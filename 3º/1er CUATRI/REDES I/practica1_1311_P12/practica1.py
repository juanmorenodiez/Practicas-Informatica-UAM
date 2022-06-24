'''
    practica1.py
    Muestra el tiempo de llegada de los primeros 50 paquetes a la interfaz especificada
    como argumento y los vuelca a traza nueva con tiempo actual

    Autor: Javier Ramos <javier.ramos@uam.es>
    2019 EPS-UAM
'''

from rc1_pcap import *
import sys
import binascii
import signal
import argparse
from argparse import RawTextHelpFormatter
import time
import logging

ETH_FRAME_MAX = 1514
PROMISC = 1
NO_PROMISC = 0
TO_MS = 10
num_paquete = 0
TIME_OFFSET = 30*60

def signal_handler(nsignal,frame):
	logging.info('Control C pulsado')
	if handle:
		pcap_breakloop(handle)


def procesa_paquete(us,header,data):
	global num_paquete, pdumper
	logging.info('Nuevo paquete de {} bytes capturado a las {}.{}'.format(header.len,header.ts.tv_sec+TIME_OFFSET,header.ts.tv_usec))
	num_paquete += 1
	num = 0
	#TODO imprimir los N primeros bytes
	for num in data[:min(args.nbytes,header.caplen)]:
		print('{:02x}'.format(num), end = ' ')
	#Escribir el tráfico al fichero de captura con el offset temporal
	print("\n")
	if pdumper is not None:
		pcap_dump(pdumper, header, data)
	


if __name__ == "__main__":
	global pdumper,args,handle
	parser = argparse.ArgumentParser(description='Captura tráfico de una interfaz ( o lee de fichero) y muestra la longitud y timestamp de los 50 primeros paquetes',
	formatter_class=RawTextHelpFormatter)
	parser.add_argument('--file', dest='tracefile', default=False,help='Fichero pcap a abrir')
	parser.add_argument('--itf', dest='interface', default=False,help='Interfaz a abrir')
	parser.add_argument('--nbytes', dest='nbytes', type=int, default=14,help='Número de bytes a mostrar por paquete')
	parser.add_argument('--debug', dest='debug', default=False, action='store_true',help='Activar Debug messages')
	args = parser.parse_args()

	if args.debug:
		logging.basicConfig(level = logging.DEBUG, format = '[%(asctime)s %(levelname)s]\t%(message)s')
	else:
		logging.basicConfig(level = logging.INFO, format = '[%(asctime)s %(levelname)s]\t%(message)s')

	if args.tracefile is False and args.interface is False:
		logging.error('No se ha especificado interfaz ni fichero')
		parser.print_help()
		sys.exit(-1)

	signal.signal(signal.SIGINT, signal_handler)

	errbuf = bytearray()
	handle = None
	pdumper = None

	#TODO abrir la interfaz especificada para captura o la traza
	#TODO abrir un dumper para volcar el tráfico (si se ha especificado interfaz)
	if args.interface is not False:
		handle = pcap_open_live(args.interface, args.nbytes, NO_PROMISC, TO_MS, errbuf)
		descr = pcap_open_dead(DLT_EN10MB, ETH_FRAME_MAX)
		pdumper = pcap_dump_open(descr, 'captura.{}.{}.pcap'.format(args.interface, time.time()))


	if args.tracefile is not False:
		handle = pcap_open_offline(args.tracefile, errbuf)
		
	if handle is None:
		print('Error %s'%errbuf)
		sys.exit(-1)

	ret = pcap_loop(handle,-1,procesa_paquete,None)
	if ret == -1:
		logging.error('Error al capturar un paquete')
	elif ret == -2:
		logging.debug('pcap_breakloop() llamado')
	elif ret == 0:
		logging.debug('No mas paquetes o limite superado')
	logging.info('{} paquetes procesados'.format(num_paquete))
	#TODO si se ha creado un dumper cerrarlo

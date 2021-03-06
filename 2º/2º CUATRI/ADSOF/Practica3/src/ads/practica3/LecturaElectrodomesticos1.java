package ads.practica3;
import java.io.*;
import java.util.*;

/**
 * Clase lectura electrodomesticos 1, del siguiente apartado, que identifica el 
 * tipo de electrodomesticoque es e imprime los datos esenciales del mismo por 
 * pantalla y separa los electrodomesticos repetidos.
 * @author Diego Cano Rueda y Juan Moreno Díez
 * @version 1.1
 * @since 1.1
 * */
public class LecturaElectrodomesticos1 {

	/**
	 * Constructor de LecturaElectrodomesticos, instacia una lista de electrodomesticos.
	 */
	static ArrayList<Electrodomestico> listaElectrodomesticos = new ArrayList<>();
	
	/**
	 * Lista de electrodomesticos repetidos.
	 */
	static ArrayList<Electrodomestico> repetidos = new ArrayList<>();
	
	/**
	 * Lee un fichero e imprime la lista de los electrodomesticos y los guarda cada uno en su
	 * lugar correspondiente identificandolos, menos a los repetidos que los almacena en una 
	 * lista a parte.
	 * @param fichero Fichero donde está la lista de electrodomesticos.
	 * @return La lista de electrodomesticos.
	 * @throws IOException excepciones.
	 */
	public static ArrayList<Electrodomestico> leer(String fichero) throws IOException {
		
		BufferedReader buffer = new BufferedReader(
				 new InputStreamReader(
				 new FileInputStream(fichero)));
		
		String linea;
		
		while((linea = buffer.readLine()) != null) {
			ClaseEnergetica tipo;
			
			String[] palabra = linea.split("=");
			
			if(palabra[3] == "A") {
				tipo = ClaseEnergetica.A;
			}
			else if(palabra[3] == "B") {
				tipo = ClaseEnergetica.B;
			}
			else if(palabra[3] == "C") {
				tipo = ClaseEnergetica.C;
			}
			else if(palabra[3] == "D") {
				tipo = ClaseEnergetica.D;
			}
			else {
				tipo = ClaseEnergetica.Desconocida;
			}
			
			/*Television*/
			if(palabra.length == 5) {
				
				Electrodomestico e = new Television(palabra[0], palabra[1],  Double.parseDouble(palabra[2]), tipo, Integer.parseInt(palabra[4]));
				
				for(Electrodomestico ele: listaElectrodomesticos) {
					if(ele.equals(e) == true) {
						repetidos.add(e);
					}
					else {
						listaElectrodomesticos.add(e);
					}
				}
			}
			
			/*Lavadora*/
			if(palabra.length == 10) {
				Electrodomestico e = new Lavadora(palabra[0], palabra[1],  Double.parseDouble(palabra[2]), tipo, new Dimension(Double.parseDouble(palabra[4]), Double.parseDouble(palabra[5]), Double.parseDouble(palabra[6])), Double.parseDouble(palabra[7]), Double.parseDouble(palabra[8]), Double.parseDouble(palabra[9]));
				listaElectrodomesticos.add(e);
			}
			
			/*Lavadora2*/
			if(palabra.length == 8) {
				Electrodomestico e = new Lavadora(palabra[0], palabra[1],  Double.parseDouble(palabra[2]), tipo, new Dimension(Double.parseDouble(palabra[4]), Double.parseDouble(palabra[5]), Double.parseDouble(palabra[6])), Double.parseDouble(palabra[7]));
				listaElectrodomesticos.add(e);
			}
			
			/*Frigorifico*/
			if(palabra.length == 9) {
				if(palabra[8] == "NoFrost") {
					Electrodomestico e = new Frigorifico(palabra[0], palabra[1],  Double.parseDouble(palabra[2]), tipo, new Dimension(Double.parseDouble(palabra[4]), Double.parseDouble(palabra[5]), Double.parseDouble(palabra[6])), Double.parseDouble(palabra[7]), true);
					listaElectrodomesticos.add(e);
				}
				else {
					Electrodomestico e = new Frigorifico(palabra[0], palabra[1],  Double.parseDouble(palabra[2]), tipo, new Dimension(Double.parseDouble(palabra[4]), Double.parseDouble(palabra[5]), Double.parseDouble(palabra[6])), Double.parseDouble(palabra[7]), false);
					listaElectrodomesticos.add(e);
				}
			}
		}
		buffer.close();
		
		return listaElectrodomesticos;
	}
}
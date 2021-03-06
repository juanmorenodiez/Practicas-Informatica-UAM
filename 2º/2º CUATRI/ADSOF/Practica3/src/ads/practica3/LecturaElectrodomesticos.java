package ads.practica3;
import java.io.*;
import java.util.*;

/**
 * Clase lectura electrodomesticos que identifica el tipo de electrodomesticoque es e imprime
 * los datos esenciales del msimo por pantalla.
 * @author Diego Cano Rueda y Juan Moreno Díez
 * @version 1.1
 * @since 1.1
 * */
public class LecturaElectrodomesticos {

	/**
	 * Constructor de LecturaElectrodomesticos, instacia una lista de electrodomesticos.
	 */
	static ArrayList<Electrodomestico> listaElectrodomesticos = new ArrayList<>();
	
	/**
	 * Lista de electrodomesticos repetidos.
	 */
	static ArrayList<Electrodomestico> repetidos = new ArrayList<>();
	
	/**
	 * Lista de electrodomesticos no repetidos.
	 */
	static ArrayList<Electrodomestico> noRepetidos = new ArrayList<>();
	
	/**
	 * Lee un fichero e imprime la lista de los electrodomesticos y los guarda cada uno en su
	 * lugar correspondiente identificandolos, menos a los repetidos que los almacena en una 
	 * lista a parte.
	 * @param fichero Fichero donde está la lista de electrodomesticos.
	 * @return La lista de electrodomesticos.
	 * @throws IOException excepciones.
	 */
	public static ArrayList<Electrodomestico> leer(String fichero) {
		try {
			BufferedReader buffer = new BufferedReader(
					 new InputStreamReader(
					 new FileInputStream(fichero)));
			
			String linea;
			
			while((linea = buffer.readLine()) != null) {
				Electrodomestico e = null;
				ClaseEnergetica tipo;
				int bandera = 0;
				
				String[] palabra = linea.split("=");
				
				if(palabra[3].equals("A")) {
					tipo = ClaseEnergetica.A;
				}
				else if(palabra[3].equals("B")) {
					tipo = ClaseEnergetica.B;
				}
				else if(palabra[3].equals("C")) {
					tipo = ClaseEnergetica.C;
				}
				else if(palabra[3].equals("D")) {
					tipo = ClaseEnergetica.D;
				}
				else {
					tipo = ClaseEnergetica.Desconocida;
				}
				
				/*Television*/
				if(palabra.length == 5) {
					e = new Television(palabra[0], palabra[1],  Double.parseDouble(palabra[2]), tipo, Integer.parseInt(palabra[4]));
				}
				
				/*Lavadora*/
				if(palabra.length == 10) {
					e = new Lavadora(palabra[0], palabra[1],  Double.parseDouble(palabra[2]), tipo, new Dimension(Double.parseDouble(palabra[4]), Double.parseDouble(palabra[5]), Double.parseDouble(palabra[6])), Double.parseDouble(palabra[7]), Double.parseDouble(palabra[8]), Double.parseDouble(palabra[9]));
				}
				
				
				/*Lavadora2*/
				if(palabra.length == 8) {
					e = new Lavadora(palabra[0], palabra[1],  Double.parseDouble(palabra[2]), tipo, new Dimension(Double.parseDouble(palabra[4]), Double.parseDouble(palabra[5]), Double.parseDouble(palabra[6])), Double.parseDouble(palabra[7]));
				}
				
				/*Frigorifico*/
				if(palabra.length == 9) {
					if(palabra[8].equals("NoFrost")) {
						e = new Frigorifico(palabra[0], palabra[1],  Double.parseDouble(palabra[2]), tipo, new Dimension(Double.parseDouble(palabra[4]), Double.parseDouble(palabra[5]), Double.parseDouble(palabra[6])), Double.parseDouble(palabra[7]), true);
					}
					else {
						e = new Frigorifico(palabra[0], palabra[1],  Double.parseDouble(palabra[2]), tipo, new Dimension(Double.parseDouble(palabra[4]), Double.parseDouble(palabra[5]), Double.parseDouble(palabra[6])), Double.parseDouble(palabra[7]), false);
					}
				}
				
				
				for (Electrodomestico ele : listaElectrodomesticos) {
					if (ele.equals(e)) {
						bandera = 1;
						repetidos.add(e);
					}
				}
				
				if (bandera == 0) {
					listaElectrodomesticos.add(e);
				}
				bandera = 0;
			}
			buffer.close();
			
			for (Electrodomestico ele : repetidos) {
				System.out.println("Duplicado no a�adido:\n" + ele);
			}
			
			return listaElectrodomesticos;
		}
		catch (IOException e){
			System.out.println (e.toString());
		}
		
		return listaElectrodomesticos;
	}
		
		
		
}
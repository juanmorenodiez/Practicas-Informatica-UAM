package ads.practica3;

import java.util.List;

/**
 * Segundo tester el tercer apartado de la P2
 * DEBE EJECUTARSE CON UN ARGUMENTO EN LA LINEA DE COMANDOS
 *
 * @param args[0] El primer unico argumento ser el nombre del archivo de texto a leer
 * @author Profesores ADS

 */

public class TesterTienda2 {
    public static void main(String[] args) {
    	List<Electrodomestico> productos = LecturaElectrodomesticos.leer( args[0] );
    	for (Electrodomestico e : productos) { 
    		System.out.println(">> " + e ); 
    	}
    	
    	// ultimo test de igualdad
    	Electrodomestico lava1 = new Lavadora("Indesit", "XWE 91483 X", 329.0,
				ClaseEnergetica.A, new Dimension(59.5, 60.5, 85.0), 72, 9.5, 1500);
        Electrodomestico frigo1 = new Frigorifico("Bosch", "KGN39VW21", 599.0,
				ClaseEnergetica.A, new Dimension(60, 65, 201), 83.0, true);
    }
}
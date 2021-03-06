package ads.practica3;

/**
 * Tester el apartado 4 de la practica 3
 * @author Diego Cano Rueda y Juan Moreno Diez.
 */
public class TesterTienda5 {
	public static void main(String[] args) {
		Dimension d1 = new Dimension(59.5, 60.5, 30.0);
		Dimension d2 = new Dimension(70, 80, 50);
		Electrodomestico tele1 = new Television("Loewe", "Art 48 4K Plata", 1699.00, ClaseEnergetica.A, 48);
        Electrodomestico teleCurva1 = new TelevisionCurva("LG", "32LF592U", 500.50, ClaseEnergetica.C, 55, d1, 15.0);
        Electrodomestico teleCurva2 = new TelevisionCurva("LG", "32LF592U", 500.50, ClaseEnergetica.C, 55, d2, 15.0);
        Electrodomestico lava1 = new Lavadora("Indesit", "XWE 91483 X", 329.0, ClaseEnergetica.A, new Dimension(59.5, 60.5, 85.0), 72, 9.5, 1500);
        
        //Creamos array de ventas y asignamos electrodomesticos a cada venta
        Venta[] ventas = new Venta[5];
        ventas[0] = new Venta(lava1);
        ventas[1] = new VentaDomicilio(tele1);
        //Para observar el coste de llevar esta television a canarias(es el ejemplo del enunciado)
        ventas[2] = new VentaCanarias(tele1);
        //Para observar diferencias al comprar dos televisiones curvas distintas y ver la diferencia del coste porte
        ventas[3] = new VentaDomicilio(teleCurva1, tele1);
        ventas[4] = new VentaDomicilio(teleCurva2, tele1);
        
        for (Venta v : ventas) {
        	System.out.println(v.getTicket());
        }

	}
}

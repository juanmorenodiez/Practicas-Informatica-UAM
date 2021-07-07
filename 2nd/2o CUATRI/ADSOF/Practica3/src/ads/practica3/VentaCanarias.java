package ads.practica3;
import java.text.DecimalFormat;
import java.text.DecimalFormatSymbols;

/**
 * Clase VentaCanarias, que intractua con los distintos tipo de electrodomesticos y calcula precios totales,
 * teniendo en cuanta algunos precios de entrega o que cada electrodomestico tiene precios
 * distintos y que el transporte es a canarias.
 * @author Diego Cano Rueda y Juan Moreno Díez
 * @version 1.1
 * @since 1.1
 * */
public class VentaCanarias extends Venta{

	/**
	 * Constructor de la clase VentaCanarias.
	 * @param eV Electrodomestico que esta a la venta.
	 */
	public VentaCanarias(Electrodomestico eV) {
		super(eV);
	}
	
	/**
	 * El precio extra que se le anade a la venta por ser de canarias.
	 * @return precio extra.
	 */
	public double ExtraCanarias() {
		return this.getElectrodomesticoVenta().getPrecioBase() * 0.07;
	}
	
	/**
     * Calcula el precio total de un electrodomestico, restando el descuento al precio base
     * y sumando el extra por ser de canarias.
     * @return importe a pagar por el usuario que compre el electrodomestico.
     */
	public double precioTotal() {
		return this.getElectrodomesticoVenta().getPrecioBase()  + this.ExtraCanarias();
	}
	
	/**
	    * Imprime la primera linea del ticket para el usuario, que contiene los productos vendidos.
	    * @return Primera linea del ticket para el usuario.
	    */
	public String getLinea1() {
    	DecimalFormatSymbols separadoresPersonalizados = new DecimalFormatSymbols();
    	separadoresPersonalizados.setDecimalSeparator('.');
    	DecimalFormat formato = new DecimalFormat("#.00", separadoresPersonalizados);
    	return "Producto vendido: " + this.getElectrodomesticoVenta().getMarca() + " " +
                this.getElectrodomesticoVenta().getModelo() + ", " + formato.format(this.getElectrodomesticoVenta().getPrecioBase()) + " Euros\n";
    }
    
	/**
	    * Imprime la segunda linea del ticket para el usuario, que contiene los precos de los productos.
	    * @return Segunda linea del ticket para el usuario.
	    */
    public String getLinea2() {
    	DecimalFormatSymbols separadoresPersonalizados = new DecimalFormatSymbols();
    	separadoresPersonalizados.setDecimalSeparator('.');
    	DecimalFormat formato = new DecimalFormat("#.00", separadoresPersonalizados);
    	return "Precio producto:     " + formato.format(this.getElectrodomesticoVenta().getPrecioBase()) + " Euros\n";
    }
    
    /**
     * Imprime la tercera linea del ticket para el usuario, que contiene los extras de cada producto
     * por ser uan venta a canarias.
     * @return Tercera linea del ticket para el usuario.
     */
    public String getLinea3() {
    	DecimalFormatSymbols separadoresPersonalizados = new DecimalFormatSymbols();
    	separadoresPersonalizados.setDecimalSeparator('.');
    	DecimalFormat formato = new DecimalFormat("#.00", separadoresPersonalizados);
    	return "Extra Canarias:         " + formato.format(this.ExtraCanarias()) + " Euros \n";
    }
    
    /**
     * Imprime el total del producto aplicando el descuento.
     * @return precio total con el descuento aplicado.
     */
    public String getTotal() {
    	DecimalFormatSymbols separadoresPersonalizados = new DecimalFormatSymbols();
    	separadoresPersonalizados.setDecimalSeparator('.');
    	DecimalFormat formato = new DecimalFormat("#.00", separadoresPersonalizados);
    	return "TOTAL:              "               + formato.format(this.precioTotal()) + " Euros\n";
    }

    /**
     * Imprime el ticket de todos los productos que un usuario haya comprado.
     * @return El ticket que se mostraria al usuario.
     */
    public String getTicket() {
        return "--------------------------------------------\n" +
                this.getLinea1()
                +"-------------------------------------------- \n" +
                this.getLinea2() +
                this.getLinea3() +
                this.getTotal();
    }
}

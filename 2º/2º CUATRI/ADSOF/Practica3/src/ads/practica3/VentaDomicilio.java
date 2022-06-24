package ads.practica3;
import java.text.*;

/**
 * Clase VentaDomicilio es un extends de Venta, se le añade la posibilidad de vender productos a domicilio.
 * @author Diego Cano Rueda y Juan Moreno Díez
 * @version 1.1
 * @since 1.1
 * */
public class VentaDomicilio extends Venta {
	
	/**
	 * Constructor de la clase VentaDomicilio.
	 * @param eV Electrodomestico que esta a la venta.
	 * @param eE Electrodomestico que se va a entregar.
	 */
    public VentaDomicilio(Electrodomestico eV, Electrodomestico eE) {
        super(eV, eE);
    }

    /**
     * Constructor de la clase VentaDomicilio.
     * @param eV Electrodomestico que esta a la venta.
     */
    public VentaDomicilio(Electrodomestico eV) {
        super(eV);
    }

    /**
     * Calcula el precio total de la venta de los electrodomesticos sumandole el precio de 
     * entrega a domicilio.
     * @return Precio total de la compra.
     */
    public double precioTotal(){
        return this.getElectrodomesticoVenta().getPrecioBase() - this.descuento() + this.getElectrodomesticoVenta().precioEntrega();
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
     * Imprime la tercera linea del ticket para el usuario, que contiene los descuentos de cada producto.
     * @return Tercera linea del ticket para el usuario.
     */
    public String getLinea3() {
    	DecimalFormatSymbols separadoresPersonalizados = new DecimalFormatSymbols();
    	separadoresPersonalizados.setDecimalSeparator('.');
    	DecimalFormat formato = new DecimalFormat("#.00", separadoresPersonalizados);
    	return "Descuento entrega:   " + formato.format(this.descuento()) + " Euros\n";
    }

    /**
     * Imprime la cuarta linea del ticket para el usuario, que contiene los precios de cada producto por el traslado si lo hay.
     * @return Cuarta linea del ticket para el usuario.
     */
    public String getLinea4() {
    	DecimalFormatSymbols separadoresPersonalizados = new DecimalFormatSymbols();
    	separadoresPersonalizados.setDecimalSeparator('.');
    	DecimalFormat formato = new DecimalFormat("#.00", separadoresPersonalizados);
    	return "Coste porte:         " + formato.format(this.getElectrodomesticoVenta().precioEntrega()) + " Euros \n";
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
     * Imprime el ticket de un usuario que haya comprado una lista de electrodomesticos.
     * @return El ticket del usuario.
     */
    public String getTicket() {
        return "--------------------------------------------\n" +
                this.getLinea1()
                +"-------------------------------------------- \n" +
                this.getLinea2() +
                this.getLinea3() +
                this.getLinea4() +
                this.getTotal();
    }

}

package ads.practica3;
import java.text.DecimalFormat;
import java.text.DecimalFormatSymbols;
import java.util.*;

/**
 * Clase Venta, que intractua con los distintos tipo de electrodomesticos y calcula precios totales,
 * teniendo en cuanta algunos precios de entrega o que cada electrodomestico tiene precios
 * distintos.
 * @author Diego Cano Rueda y Juan Moreno Díez
 * @version 1.1
 * @since 1.1
 * */
public class Venta {
	
	/**
	 * Electrodomestico que esta a la venta.
	 */
    private Electrodomestico electrodomesticoVenta;
    
    /**
     * Electrodomestico que hay que entregar.
     */
    private Electrodomestico electrodomesticoEntrega;
    
    /**
     * Instaciacion de un Array List de ventas.
     */
    private static ArrayList<Venta> ventas = new ArrayList<>();

    /**
     * Constructor de la clase Venta.
     * @param eV Electrodomestico que esta a la venta.
     * @param eE Electrodomestico que hay que entregar.
     */
    public Venta(Electrodomestico eV, Electrodomestico eE) {
        this.electrodomesticoVenta = eV;
        this.electrodomesticoEntrega = eE;
        ventas.add(this);   
    }

    /**
     * Constructor de Venta de electrodomesticos
     * @param eV Electrodomestico que esta a la venta.
     */
    public Venta(Electrodomestico eV) {
        this.electrodomesticoVenta = eV;
        ventas.add(this);
    }

    /**
     * Getter de Electrodomestico en venta.
     * @return electrodomesticoVenta Electrodomestico que esta a la venta.
     */
    public Electrodomestico getElectrodomesticoVenta() {
        return electrodomesticoVenta;
    }

    /**
     * Setter de electrodomestico a la venta.
     * @param electrodomesticoVenta Electrodomestico que se pone en venta.
     */
    public void setElectrodomesticoVenta(Electrodomestico electrodomesticoVenta) {
        this.electrodomesticoVenta = electrodomesticoVenta;
    }

    /**
     * Getter de Electrodomestico en entrega.
     * @return electrodomesticoEntrega Electrodomestico que esta para entregar.
     */
    public Electrodomestico getElectrodomesticoEntrega() {
        return electrodomesticoEntrega;
    }

    /**
     * Setter de electrodomestico en entrega.
     * @param electrodomesticoEntrega Electrodomestico que se pone en entrega.
     */
    public void setElectrodomesticoEntrega(Electrodomestico electrodomesticoEntrega) {
        this.electrodomesticoEntrega = electrodomesticoEntrega;
    }

    /**
     * Calcula el descuento que se hace a ciertos Electrodomesticos.
     * @return descuento aplicable a cada electrodomesticos, no es el mismo para todos.
     */
    public double descuento() {
        int entrega;
        int venta;

        if (electrodomesticoEntrega == null) {
            return 0;
        }

        venta = this.getElectrodomesticoVenta().getClaseEnergetica().getValor();
        entrega = this.getElectrodomesticoEntrega().getClaseEnergetica().getValor();


        if (entrega == venta && entrega != 4) {
            return 25.0;
        }

        else if (entrega < venta && entrega != 4) {
            venta -= entrega;

            return 25 - (5 * venta);
        }

        else if (entrega > venta && entrega != 4) {
            entrega -= venta;

            return 25 + (15 * entrega);
        }

        else
            return 10;
    }

    /**
     * Calcula el precio total de un electrodomestico, restando el descuento al precio base.
     * @return importe a pagar por el usuario que compre el electrodomestico.
     */
    public double precioTotal(){
        return electrodomesticoVenta.getPrecioBase() - this.descuento();
    }
    
    /**
     * Metodo que imprime el ultimo electrodomestico que se ha vendido
     * @return Ultimo electrodomestico vendido.
     */
    public static Venta ultima() {
    	return ventas.get(ventas.size() - 1);
    }
    
    /**
     * Resumen de todas las ventas de una Venta.
     * @return String de todas las ventas realizadas hasta el momento de una venta.
     */
    public static String resumenVentas() {
    	String resumen = "\nRESUMEN DE VENTAS\n";
    	
    	for (int i = 0; i < ventas.size(); i++) {
    		resumen += ventas.get(i).getTotal();
    	}
    	
    	return resumen;
    }
    
    /**
     * Resumen de todas las ventas de una venta teniendo en cuenta de cuanto dinero 
     * dispone el que hace la venta y eliminando los productos posteriores.
     * @param importe dinero disponible por el comprador.
     * @return String de todas las ventas que se puede permitir el usuario.
     */
    public static String resumenVentas(int importe) {
    	String resumen = "\nRESUMEN DE VENTAS\n";
    	
    	for (int i = 0; i < ventas.size(); i++) {
    		if (ventas.get(i).precioTotal() > importe) {
    			resumen += ventas.get(i).getTotal();
    		}
    	}
    	
    	return resumen;
    }
    
    /**
     * Resumen de las ventas de una venta que coincida con la cadena que se pasa por argumento.
     * @param cadena Cadena que se debe repetir.
     * @return Resumen de la venta.
     */
    public static String resumenVentas(String cadena) {
    	String resumen = "\nRESUMEN DE VENTAS\n";
    	
    	for (int i = 0; i < ventas.size(); i++) {
    		if (ventas.get(i).electrodomesticoVenta.getMarca().equals(cadena)) {
    			resumen += ventas.get(i).getTotal();
    		}
    	} 	
    	return resumen;
    }
    
   /**
    * Anula una venta entera. 
    * @return la venta borrada.
    */
   public static Venta anular() {
	   Venta v;
	   
	   v = ventas.get(ventas.size() -1);
	   
	   ventas.remove(v);
	   
	   return v;
	   
   }
    
   /**
    * Imprime la primera linea del ticket para el usuario, que contiene los productos vendidos.
    * @return Primera linea del ticket para el usuario.
    */
   public String getLinea1() {
	   DecimalFormatSymbols separadoresPersonalizados = new DecimalFormatSymbols();
	   separadoresPersonalizados.setDecimalSeparator('.');
	   DecimalFormat formato = new DecimalFormat("#.00", separadoresPersonalizados);
	   return "Producto vendido: " + electrodomesticoVenta.getMarca() + " " +
       			electrodomesticoVenta.getModelo() + ", " + formato.format(electrodomesticoVenta.getPrecioBase()) + " Euros\n";
    }
    
   /**
    * Imprime la segunda linea del ticket para el usuario, que contiene los precos de los productos.
    * @return Segunda linea del ticket para el usuario.
    */
   public String getLinea2() {
	   DecimalFormatSymbols separadoresPersonalizados = new DecimalFormatSymbols();
	   separadoresPersonalizados.setDecimalSeparator('.');
	   DecimalFormat formato = new DecimalFormat("#.00", separadoresPersonalizados);
	   return "Precio producto:    " + formato.format(electrodomesticoVenta.getPrecioBase()) + " Euros\n";
    }
    
   /**
    * Imprime la tercera linea del ticket para el usuario, que contiene los descuentos de cada producto.
    * @return Tercera linea del ticket para el usuario.
    */
   public String getLinea3() {
	   DecimalFormatSymbols separadoresPersonalizados = new DecimalFormatSymbols();
	   separadoresPersonalizados.setDecimalSeparator('.');
	   DecimalFormat formato = new DecimalFormat("#.00", separadoresPersonalizados);
	   return "Descuento entrega:  " + formato.format(this.descuento()) + " Euros\n";
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
                + "-------------------------------------------- \n" +
                this.getLinea2() +
                this.getLinea3() +
                this.getTotal();
    }
}

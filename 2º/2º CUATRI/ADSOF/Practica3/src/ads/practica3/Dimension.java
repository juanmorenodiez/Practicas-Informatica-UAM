package ads.practica3;

/**
 * Describe las dimensiones de los electrodomesticos 
 * y calcula su volumen.
 * @author Diego Cano Rueda y Juan Moreno Díez
 * @version 1.1
 * @since 1.1
 * */
public class Dimension {
	
	/**
	 * Describe el ancho del electrodomestico
	 */
    private double ancho;
    
    /**
     * Describe el fondo del electrodomestico.
     */
    private double fondo;
    
    /**
     * Describe el alto del electrodomestico.
     */
    private double alto;

    /**
     * Constructor de la clase Dimension.
     * @param x el ancho del electrodomestico
     * @param y el fondo del electrodomestico
     * @param z el alto del electrodomestico
     */
    public Dimension(double x, double y, double z) {
        this.ancho = x;
        this.fondo = y;
        this.alto = z;
    }

    /**
    * 
    * @return calcula la dimension total de un electrodomesticos mediante
    * su ancho, su fondo y su altura.
    */
    public double calcularDimension(){
        return (this.ancho * 0.01) + (this.fondo * 0.01) + (this.alto * 0.01);
    }
}

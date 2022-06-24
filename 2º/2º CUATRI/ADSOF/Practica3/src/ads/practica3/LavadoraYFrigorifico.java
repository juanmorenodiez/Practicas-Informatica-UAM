package ads.practica3;

/**
 * Clase lavadoraYFrigorifico que describe algunos parametros adicionales propios de las lavadoras y los frigorificos,
 * extends de la clase Electrodomestico.
 * @author Diego Cano Rueda y Juan Moreno Díez
 * @version 1.1
 * @since 1.1
 * */
public class LavadoraYFrigorifico extends Electrodomestico{
    
	/**
	 * Dimensiones de la lavadora o del frigorifico.
	 */
	private Dimension dimensiones;
	
	/**
     * Peso de la lavadora o del frigorifico.
     */
    private double peso;

    /**
     * Constructor de la clase LavadoraYFrigorifico.
     * @param marca Marca de la lavadora o del frigorifico.
     * @param modelo Modelo de la lavadora o del frigorifico.
     * @param precioBase Precio inicial de la lavadora o del frigorifico.
     * @param claseEnergetica Clase Energetica de la lavadora o del frigorifico.
     * @param d Dimension de la lavadora o del frigorifico.
     * @param p Precio de transporte de la lavadora o del frigorifico.
     */
    public LavadoraYFrigorifico(String marca, String modelo, double precioBase, ClaseEnergetica claseEnergetica, Dimension d, double p) {
        super(marca, modelo, precioBase, claseEnergetica);
        this.dimensiones = d;
        this.peso = p;
    }

    /**
     * Precio de entrega de la lavadora o del frigorifico que siempre es 0.
     */
    public double precioEntrega() {
        return 0;
    }

    /**
     * Setter del peso de la lavadora o del frigorifico.
     * @param peso peso nuevo de la lavadora o del frigorifico.
     */
    public void setPeso(double peso) {
        this.peso = peso;
    }

    /**
     * Getter del peso de la lavadora o del frigorifico.
     * @return peso de la lavadora o del frigorifico.
     */
    public double getPeso() {
        return peso;
    }

    /**
     * Setter de las dimensiones de la lavadora o del frigorifico.
     * @param dimensiones Dimensiones nuevas de la lavadora o del frigorifico.
     */
    public void setDimensiones(Dimension dimensiones) {
        this.dimensiones = dimensiones;
    }

    /**
     * Getter de las dimensiones de la lavadora o del frigorifico.
     * @return dimensiones Dimensiones de la lavadora o del frigorifico.
     */
    public Dimension getDimensiones() {
        return dimensiones;
    }
    
    /**
     * Para imprimir la marca, el modelo y el precio inicial de la lavadora o el frigorifico.
     * @return Linea que se imprimira por pantalla.
     */
    public String ToString() {
		return this.getMarca() + " "+ this.getModelo() + ", " + this.getPrecioBase() + " Euros";
	}
}

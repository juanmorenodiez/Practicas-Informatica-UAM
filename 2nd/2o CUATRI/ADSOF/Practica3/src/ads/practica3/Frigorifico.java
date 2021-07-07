package ads.practica3;

/**
* Clase frigorifico que describe las caracteristicas adicionales que tiene a parte de las
* descritas en la clase electrodomestico.
* @author Diego Cano Rueda y Juan Moreno Díez
* @version 1.1
* @since 1.1
* */
public class Frigorifico extends LavadoraYFrigorifico {
	
	/**
	 * Si el frigorifico es frost o no.
	 */
    private boolean esNofrost;

    /**
	 * Constructor de la clase frigorifico
	 * @param marca Marca del Frigorifico.
	 * @param modelo Modelo del Frigorifico.
	 * @param precioBase precio inicial del Frigorifico.
	 * @param claseEnergetica clase eneregetica del Frigorifico.
	 * @param d dimension del Frigorifico.
	 * @param p precio de entrega del Frigorifico.
	 * @param esNofrost si es frost o no el Frigorifico.
	 */
    public Frigorifico(String marca, String modelo, double precioBase, ClaseEnergetica claseEnergetica, Dimension d, double p, boolean esNofrost) {
        super(marca, modelo, precioBase, claseEnergetica, d, p);
        this.setEsNofrost(esNofrost);
    }

    /**
     * Calcula el precio de la entrega del Frigorifico.
     * @return Precio de la entrega del Frigorifico.
     */
    @Override
    public double precioEntrega() {
        return (int) (this.getDimensiones().calcularDimension() * 70);
    }

    /**
     * Getter de EsNoFrost el Frigorifico.
     * @return si es frost o no el Frigorifico.
     */
	public boolean isEsNofrost() {
		return esNofrost;
	}

	/**
	 * Setter de esNoFrost del Frigorifico.
	 * @param esNofrost el cambio que se le quiere hacer al Frigorifico.
	 */
	public void setEsNofrost(boolean esNofrost) {
		this.esNofrost = esNofrost;
	}
	
	/**
	 * Para imprimir por pantalla la marca, el modelo y el precio inicial del Frigorifico.
	 * @return linea que se imprimira por pantalla.
	 */
	public String toString() {
		return this.getMarca() + " "+ this.getModelo() + ", " + this.getPrecioBase() + " Euros";
	}
}

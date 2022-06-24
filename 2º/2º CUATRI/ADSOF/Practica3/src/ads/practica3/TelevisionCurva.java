package ads.practica3;

/**
 * Clase TelevisionCurva que describe algunos parametros adicionales propios de las televisiones curvas,
 * extends de la clase Television.
 * @author Diego Cano Rueda y Juan Moreno Díez
 * @version 1.1
 * @since 1.1
 * */
public class TelevisionCurva extends Television{
	
	/**
	 * Dimensiones de la television curva.
	 */
	private Dimension dimensiones;
	
	/**
	 * Peso de la television curva.
	 */
	private double peso;
	
	/**
	 * 
	 * @param marca Marca de la television.
     * @param modelo Modelo de la television.
     * @param precioBase Precio inicial de la television.
     * @param claseEnergetica Clase energetica de la television.
     * @param dim Dimension de la television.
	 * @param d Dimensiones de la television curva.
	 * @param peso Peso de la television curva.
	 */
	public TelevisionCurva(String marca, String modelo, double precioBase, ClaseEnergetica claseEnergetica, Integer dim, Dimension d, double peso) {
		super(marca, modelo, precioBase, claseEnergetica, dim);
		this.setDimensiones(d);
		this.peso = peso;
	}

	/**
	 * Getter de peso de la television curva.
	 * @return peso de la television curva.
	 */
	public double getPeso() {
		return peso;
	}

	/**
	 * Setter del peso de la television curva.
	 * @param peso Nuevo peso de la television curva.
	 */
	public void setPeso(double peso) {
		this.peso = peso;
	}

	/**
	 * Getter de las dimensiones de la television curva.
	 * @return dimensiones de la television curva.
	 */
	public Dimension getDimensiones() {
		return dimensiones;
	}

	/**
	 * Setter de las dimensiones de la television curva.
	 * @param dimensiones Nuevas dimensiones de la television curva.
	 */
	public void setDimensiones(Dimension dimensiones) {
		this.dimensiones = dimensiones;
	}
	
	/**
     * Este metodo calcula el precio de entrega de la television segun sus dimensiones.
     * @return precio Precio de la entrega
     */
	@Override
	public double precioEntrega () {
		double porteTelevision;
		double volumen;
		
		porteTelevision = super.precioEntrega();
		volumen = this.dimensiones.calcularDimension() * 25.00;
		System.out.println(volumen);
		
		return porteTelevision + volumen;
	}
}

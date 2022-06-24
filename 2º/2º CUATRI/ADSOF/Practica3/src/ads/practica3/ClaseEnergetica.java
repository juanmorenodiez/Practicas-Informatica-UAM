package ads.practica3;

/**
 * Esta enumeracion describe si el electrodomestico 
 * es de un tipo o si se desconoce.
 * @author Diego Cano Rueda y Juan Moreno Díez
 * @version 1.1
 * @since 1.1
 * */
public enum ClaseEnergetica {
	
    A(0), B(1), C(2), D(3), Desconocida(4);

	/**
	 * Constructor de la enumeracion Clase Energetica.
	 * @version 1.1
	 * @since 1.1
	 * @param v el valor de la clase energetica.
	 */
    private ClaseEnergetica(int v) {
        this.valor = v;
    }
    
    /**
     * Variable valor que no se puede modificar.
     */
    private final int valor;

    /**
     * Getter de la enumeracion ClaseEnergetica.
     * @return el valor de la clase energetica del electrodomestico
     */
    public int getValor() {
        return valor;
    }
}

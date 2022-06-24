package ads.practica3;

/**
 * Clase Television que describe algunos parametros adicionales propios de las televisiones,
 * extends de la clase Electrodomestico.
 * @author Diego Cano Rueda y Juan Moreno Díez
 * @version 1.1
 * @since 1.1
 * */
public class Television extends Electrodomestico {
    
	/**
	 * Dimension de la television.
	 */
	private Integer dimension;

	/**
     * Constructor de la clase Television.
     * @param marca Marca de la television.
     * @param modelo Modelo de la television.
     * @param precioBase Precio inicial de la television.
     * @param claseEnergetica Clase energetica de la television.
     * @param dim Dimension de la television.
     */
    public Television(String marca, String modelo, double precioBase, ClaseEnergetica claseEnergetica, Integer dim) {
        super(marca, modelo, precioBase, claseEnergetica);
        this.dimension = dim;
    }

    /**
     * Este metodo calcula el precio de entrega de la television segun sus dimensiones.
     * @return precio Precio de la entrega
     */
    @Override
    public double precioEntrega() {
        double coste = 0;
        if (dimension <= 40 && getPrecioBase() > 500) {
        	System.out.println(coste);
            return coste;
        }
        else if (dimension <= 40 && getPrecioBase() <= 500) {
        	coste += 35;
        	System.out.println(coste);
            return coste;
        }

        else {
            for (int i = 40; i < dimension; i++) {
                coste++;
            }
            coste += 35;
            System.out.println(coste);
            return coste;
        }
    }
    
    /**
     * Para imprimir la marca, el modelo y el precio inicial de la television.
     * @return Linea que se imprimira por pantalla.
     */
    public String toString() {
		return this.getMarca() + " "+ this.getModelo() + ", " + this.getPrecioBase() + " Euros";
	}
}

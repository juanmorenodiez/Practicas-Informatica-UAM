package ads.practica3;

/**
 * Clase abstracta Electrodomestico que recoge los datos comunes a las
 * lavadoras, los frigorificos y los televisores.
 * @author Diego Cano Rueda y Juan Moreno Díez
 * @version 1.1
 * @since 1.1
 * */
public abstract class Electrodomestico {
	
	/**
	 * Marca del Electrodomestico.
	 */
    private String marca;
    
    /**
     * Modelo del Electrodomestico.
     */
    private String modelo;
    
    /**
     * Precio inicial del Electrodomestico.
     */
    private double precioBase;
    
    /**
     * Clase eneregetica del Electrodomestico, A, B, C, D o Desconocido.
     */
    private ClaseEnergetica claseEnergetica;

    /**
     * Constructor del electrodomestico.
     * @param marca Marca del Electrodomestico.
     * @param modelo Modelo del Electrodomestico.
     * @param precioBase precio inicial del Electrodomestico.
     * @param claseEnergetica clase energetica del Electrodomestico.
     */
    public Electrodomestico(String marca, String modelo, double precioBase, ClaseEnergetica claseEnergetica) {
        this.marca = marca;
        this.modelo = modelo;
        this.precioBase = precioBase;
        this.claseEnergetica = claseEnergetica;
    }

    /**
     * Setter de la marca del Electrodomestico.
     * @param marca marca del Electrodomestico.
     */
    public void setMarca(String marca) {
        this.marca = marca;
    }

    /**
     * Getter de la marca del Electrodomestico.
     * @return marca del Electrodomestico.
     */
    public String getMarca() {
        return marca;
    }


    /**
     * Setter del modelo del Electrodomestico.
     * @param modelo Modelo del Electrodomestico.
     */
    public void setModelo(String modelo) {
        this.modelo = modelo;
    }

    /**
     * Getter del modelo del Electrodomestico.
     * @return Modelo del Electrodomestico.
     */
    public String getModelo() {
        return modelo;
    }

    /**
     * Setter del precio inicial del Electrodomestico.
     * @param precioBase precio inicial del Electrodomestico.
     */
    public void setPrecioBase(double precioBase) {
        this.precioBase = precioBase;
    }

    /**
     * Getter del precio inicial del Electrodomestico.
     * @return Precio inicial del Electrodomestico.
     */
    public double getPrecioBase() {
        return precioBase;
    }

    /**
     * Precio que tiene cada electrodomestico para ser entregado
     * a domicilio.
     * @return precio de la entrega.
     */
    public abstract double precioEntrega();

    /**
     * Getter de la clase energetica del Electrodomestico.
     * @return la Clase energetica del Electrodomestico.
     */
    public ClaseEnergetica getClaseEnergetica() {
        return claseEnergetica;
    }

    /**
     * Setter de la clase energetica del Electrodomestico.
     * @param claseEnergetica Clase energetica del Electrodomestico.
     */
    public void setClaseEnergetica(ClaseEnergetica claseEnergetica) {
        this.claseEnergetica = claseEnergetica;
    }
    
    /**
     * Comprueba si dos objectos(en este caso electrodomesticos) son iguales, mediante
     * su clase, su marca y su modelo.
     * @param e Objeto, en nuestro caso electrodomestico, que se quiere comprobar si es
     * igual al objeto Electrodomestico.
     * @return false si son distintos o si el objeto pasado como parametro es erroneo.
     * @return true si los dos objetos son iguales.
     */
    @Override
    public boolean equals(Object e) {
    	if (e == null) {
    		return false;
    	}
	
    	if (this.getClass().equals(e.getClass()) && this.getMarca().equals(((Electrodomestico) e).getMarca()) && this.getModelo().equals(((Electrodomestico) e).getModelo())) {
    		return true;
    	}
    	
    	return false;
    }
    

}

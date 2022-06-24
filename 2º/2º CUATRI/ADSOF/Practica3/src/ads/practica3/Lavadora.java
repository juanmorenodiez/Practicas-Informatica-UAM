package ads.practica3;

/**
 * Clase lavadora que describe algunos parametros adicionales propios de las lavadoras,
 * extends de la clase LavadoraYFrigorifico.
 * @author Diego Cano Rueda y Juan Moreno Díez
 * @version 1.1
 * @since 1.1
 * */
public class Lavadora extends LavadoraYFrigorifico {
	
	/**
	 * peso en kilos de la lavadora.
	 */
    private double kilos;
    

    /**
     * revoluciones por minuto de la lavadora.
     */
    private double rpm;

    /**
     * Constructor de la clase Lavadora, lavadora 1.
     * @param marca Marca de la lavadora.
     * @param modelo Modelo de la lavadora.
     * @param precioBase precio inicial de la lavadora.
     * @param claseEnergetica Clase eneregetica de la lavadora.
     * @param d Dimensiones de la lavadora.
     * @param kilos Peso en kilos de la lavadora.
     * @param p Precio de transporte de la lavadora.
     * @param rpm Revoluciones por minuto de la lavadora.
     */
    public Lavadora(String marca, String modelo, double precioBase, ClaseEnergetica claseEnergetica, Dimension d, double kilos, double p, double rpm) {
        super(marca, modelo, precioBase, claseEnergetica, d, p);
        this.kilos = kilos;
        this.rpm = rpm;
    }

    /**
     * Constructor de la clase lavadora, lavadora 2.
     * @param marca Marca de la lavadora.
     * @param modelo Modelo de la lavadora.
     * @param precioBase precio inicial de la lavadora.
     * @param claseEnergetica Clase eneregetica de la lavadora.
     * @param d Dimensiones de la lavadora.
     * @param p Precio de transporte de la lavadora.
     */
    public Lavadora(String marca, String modelo, double precioBase, ClaseEnergetica claseEnergetica, Dimension d, double p) {
        super(marca, modelo, precioBase, claseEnergetica, d, p);
    }

    /**
     * Setter del peso en kilos de la lavadora.
     * @param kilos kilos de la lavadora.
     */
    public void setKilos(double kilos) {
        this.kilos = kilos;
    }

    /**
     * Getter del peso en kilos de la lavadora.
     * @return kilos kilos de la lavadora.
     */
    public double getKilos() {
        return kilos;
    }

    /**
     * Setter de las revoluciones por minuto de la lavadora.
     * @param rpm revoluciones por minuto de la lavadora.
     */
    public void setRpm(double rpm) {
        this.rpm = rpm;
    }

    /**
     * Getter de las revoluciones por minuto de la lavadora.
     * @return rpm revoluciones por minuto de la lavadora.
     */
    public double getRpm() {
        return rpm;
    }

    /**
     * Calcula el precio de la entrega de la lavadora.
     * @return double , precio estimado por la entrega de la lavadora.
     */
    @Override
    public double precioEntrega() {
        double adicional = 0;

        if (this.getKilos() <= 50) {
            return 35;
        }

        else if (this.getKilos() > 50) {
            for (int i = 51; i <= this.getKilos(); i++) {
                adicional += 0.50;
            }

            return 35 + adicional;
        }
        else
            return 0;
    }
    
    /**
     * Para imprimir la marca, el modelo y el precio inicial de la lavadora.
     * @return Linea que se imprimira por pantalla.
     */
    public String toString() {
		return this.getMarca() + " "+ this.getModelo() + ", " + this.getPrecioBase() + " Euros";
	}
}

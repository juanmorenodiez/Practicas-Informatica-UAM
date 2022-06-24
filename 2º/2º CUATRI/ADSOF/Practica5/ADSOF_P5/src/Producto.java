import java.util.Date;
import java.util.concurrent.TimeUnit;

/**
 * Clase Producto que describe su precio y la caducidad mediante
 * un formato de tipo fecha.
 * 
 * @author Diego cano y Juan Moreno
 * @version 1.2
 * @since 1.1
 */
public class Producto {
	
	/**
	 * Precio del producto.
	 */
	private double precio;
	
	/**
	 * Caducidad del producto.
	 */
	private Date caducidad; // Otra opci�n es usar Calendar
	
	/**
	 * Constructor del producto.
	 * @param p precio del producto.
	 * @param c caducidad del producto.
	 */
	public Producto (double p, Date c) {
		this.precio = p;
		this.caducidad = c;
	}
	
	/**
	 * Getter del precio del producto.
	 * @return Precio del producto.
	 */
	public double getPrecio() { 
		return this.precio; 
	}
	
	/**
	 * Setter del precio del producto.
	 * @param p Precio del producto.
	 */
	public void setPrecio(double p) {
		this.precio = p;
	}
	
	/**
	 * Getter de la caducidad del producto.
	 * @return Caducidad del producto.
	 */
	public Date getCaducidad() { 
		return this.caducidad; 
	}
	
	/**
	 * Getter de la diferencia entre caducidades de productos.
	 * @param date1 Fecha 1 del producto.
	 * @param date2 Fecha 2 del producto.
	 * @param timeUnit Unidad de tiempo del producto.
	 * @return Diferencia entre fechas de los productos.
	 */
	public static long getDateDiff(Date date1, Date date2, TimeUnit timeUnit) {
		long diffInMillies = date2.getTime() - date1.getTime();
		return timeUnit.convert(diffInMillies,TimeUnit.MILLISECONDS);
	}
	
	/**
	 * Metodo toString del producto.
	 * @return
	 */
	@Override
	public String toString() {
		return this.precio+", caducidad: "+this.caducidad; 
	}
}

package ads.p2.facturacion;

public class Libro extends Articulo {
	private String categoria;
	  public Libro(long id, String desc, double precio, String cat) {
		super(id, desc, precio);
		categoria = cat;
	  }
	  public String getCategoria() { return categoria; }
	  public void setCategoria(String cat) { categoria = cat; }
	  public double tipoIVA() { return 0.04; }
	  public double descuento(double unidades) {
	        if (categoria == "LibroDeTexto") return getPrecioUnitario() * (int) (unidades) * 0.15;
	        else if (categoria == "Coleccion" && ((int) (unidades)) > 2) return getPrecioUnitario()	* 2 + (((int) (unidades) - 2) * getPrecioUnitario() * 0.5);
	        else return 0;
      }
}

package ads.p2.facturacion;

public class Tabaco extends Articulo {
	  public Tabaco(long id, String desc, double precio) {
		super(id, desc, precio);
	  }
	  public double descuento(double unidades) { return 0; }
}
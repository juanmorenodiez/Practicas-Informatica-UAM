package ads.p2.facturacion;

public class Alimento extends Articulo {
	  private boolean promo3x2;
	  public Alimento(long id, String desc, double precio, boolean promo) {
		super(id, desc, precio);
		promo3x2 = promo;
	  }
	  public boolean getPromo3x2() { return promo3x2; }
	  public void setPromo3x2(boolean promo) { promo3x2 = promo; }
	  public double tipoIVA() { return 0.10; }
	  public double descuento(double unidades) {
	        if (promo3x2) return getPrecioUnitario() * (int) (unidades / 3);
	        else return 0.0;		
	  }
}
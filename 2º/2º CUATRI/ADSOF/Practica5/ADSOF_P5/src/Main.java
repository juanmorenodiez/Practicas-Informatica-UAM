import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;
import java.util.concurrent.TimeUnit;

/**
 * Clase Main de prueba para el apartado 3 de la practica
 * 
 * @author Diego cano y Juan Moreno
 * @version 1.5
 * @since 1.1
 */
public class Main {
	public static void main(String...args) throws ParseException {
		SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yyyy");
		RuleSet<Producto> rs = new RuleSet<Producto>(); // Un conjunto de reglas aplicables sobre Productos
		
		rs.add(
				Rule.<Producto>rule("r1", "Rebaja un 10% los productos con fecha de caducidad cercana o pasada").
					when(pro -> Producto.getDateDiff(Calendar.getInstance().getTime(), pro.getCaducidad(), TimeUnit.DAYS) < 2 ).
					exec(pro -> pro.setPrecio(pro.getPrecio()-pro.getPrecio()*0.1))
				).add(
				Rule.<Producto>rule("r2", "Rebaja un 5% los productos que valen m�s de 10 euros").
					when(pro -> pro.getPrecio() > 10).
					exec(pro -> pro.setPrecio(pro.getPrecio()-pro.getPrecio()*0.05))
		);
		
		List<Producto> str = Arrays.asList(new Producto(10, sdf.parse("15/04/2020")), new Producto(20, sdf.parse("20/03/2021")));

		rs.setExecContext(str); // indicamos que el conjunto de reglas rs se ejecutar� sobre str
		rs.process(); // ejecutamos el conjunto de reglas
		System.out.println(str); // imprimimos str
		
	}
}

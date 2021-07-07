package Proyectos;
import java.util.*;

import Usuarios.*;

public class ProyectoInfraestructura extends Proyecto {
	private String imagen;
	private ArrayList<Distrito> distritos;
	
	
	public ProyectoInfraestructura(String titulo, String descr, Date fecha, String imagen) {
		super(titulo, descr, fecha);
		this.imagen = imagen;
		this.distritos = new ArrayList<Distrito>();
	}


	public String getImagen() {
		return imagen;
	}


	public void setImagen(String imagen) {
		this.imagen = imagen;
	}
	
	
	public void addDistrito(Distrito d) {
		if(d == null) {
			return;
		}
		this.distritos.add(d);
	}
	

}

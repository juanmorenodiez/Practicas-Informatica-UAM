package Proyectos;

import java.util.*;

public class ProyectoSocial extends Proyecto {
	private String descripcionGrupoSocial;
	
	public ProyectoSocial(String titulo, String descripcion, Date fecha, String descr) {
		super(titulo, descripcion, fecha);
		this.setDescripcionGrupoSocial(descr);
	}

	public String getDescripcionGrupoSocial() {
		return descripcionGrupoSocial;
	}

	public void setDescripcionGrupoSocial(String descripcionGrupoSocial) {
		this.descripcionGrupoSocial = descripcionGrupoSocial;
	}

}

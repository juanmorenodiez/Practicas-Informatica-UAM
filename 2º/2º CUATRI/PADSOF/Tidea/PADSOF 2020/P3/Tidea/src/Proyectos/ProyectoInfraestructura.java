package Proyectos;

import java.util.*;
import Usuarios.*;


/**
 * Clase Proyecto infraestructura es un extend de proyecto que ademas de tener
 * los atrivutos de proyecto tiene una imagen de la infraestructura y una lista
 * de distritos a los que afectaria.
 * 
 * @author Diego Cano, Juan Moreno y Julio Carreras.
 * @version 1.4
 * @since 1.1
 */
public class ProyectoInfraestructura extends Proyecto {

	/**
	 * serialVersionUID que implementa Serializable
	 */
	private static final long serialVersionUID = 1L;

	/**
	 * Imagen del plano del proyecto de infraestructura.
	 */
	private String imagen;

	/**
	 * Distritos del proyecto de infraestructura.
	 */
	private ArrayList<Distrito> afectados;

	/**
	 * Constructor del proyecto de infraestructura.
	 * 
	 * @param titulo            Titulo del proyecto de infraestructura.
	 * @param descr             Descripcion del proyecto de infraestructura.
	 * @param importeSolicitado Importe solicitado del proyecto de infraestructura.
	 * @param imagen            Imagen del plano del proyecto de infraestructura.
	 */
	public ProyectoInfraestructura(String titulo, String descr, double importeSolicitado, String imagen) {
		super(titulo, descr, importeSolicitado);
		this.imagen = imagen;
		this.afectados = new ArrayList<Distrito>();
	}

	/**
	 * Getter de la lista de distritos afectados por el proyecto
	 * 
	 * @return lista con nombres de los distritos
	 */
	public ArrayList<Distrito> getAfectados() {
		return afectados;
	}

	/**
	 * Metodo que reemplaza una lista por otra
	 * 
	 * @param distritos lista de distritos
	 */
	public void setDistritos(ArrayList<Distrito> distritos) {
		this.afectados = distritos;
	}

	/**
	 * Getter de la imagen del plano del proyecto de infraestructura.
	 * 
	 * @return Imagen del plano del proyecto de infraestructura.
	 */
	public String getImagen() {
		return imagen;
	}

	/**
	 * Setter de la imagen del plano del proyecto de infraestructura.
	 * 
	 * @param imagen Imagen del plano del proyecto de infraestructura.
	 */
	public void setImagen(String imagen) {
		this.imagen = imagen;
	}

	/**
	 * Anade distrito a la lista de distritos del proyecto de infraestructura.
	 * 
	 * @param d Distrito a anadir a la lista de distritos del proyecto de
	 *          infraestructura.
	 */
	public void addDistrito(Distrito d) {
		if (d == null) {
			return;
		}
		this.afectados.add(d);
	}

	/**
	 * Getter de datos estra de un proyecto de tipo
	 * infraestructura
	 * 
	 * @return datos extra
	 */
	@Override
	public String getExtraData() {
		return "Extra Data";
	}

	/**
	 * Getter de la descripcion de un proyecto de tipo
	 * infraestructura
	 * 
	 * @return descripcion del proyecto
	 */
	@Override
	public String getProjectDescription() {
		return this.getDescripcion();
	}

	/**
	 * Getter del tipo un proyecto de tipo
	 * infraestructura
	 * 
	 * @return tipo del proyecto
	 */
	@Override
	public ProjectKind getProjectKind() {
		return ProjectKind.Infrastructure;
	}

	/**
	 * Getter del titulo de un proyecto de tipo
	 * infraestructura
	 * 
	 * @return titulo del proyecto
	 */
	@Override
	public String getProjectTitle() {
		return this.getTitulo();
	}

	/**
	 * Getter de la cantidad de un proyecto de tipo
	 * infraestructura
	 * 
	 * @return cantidad que el proyecto ha solicitado
	 */
	@Override
	public double getRequestedAmount() {
		return this.getImporteSolicitado();
	}

}

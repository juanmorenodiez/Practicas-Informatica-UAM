package Proyectos;

/**
 * La clase de proyecto social es un extends de la clase proyecto pero que
 * ademas se necesita una desccripcion social para que el proyecto lo pueda
 * validar o no el administrador.
 * 
 * @author Diego Cano, Juan Moreno y Julio Carreras.
 * @version 1.7
 * @since 1.1
 */
public class ProyectoSocial extends Proyecto {

	/**
	 * serialVersionUID para Serializable.
	 */
	private static final long serialVersionUID = 1L;

	/**
	 * Descripcion del grupo social al que pertenece el proyecto
	 */
	private String descripcionGrupoSocial;

	/**
	 * Si el proyecto social es nacional o no.
	 */
	private boolean esNacional;

	/**
	 * Constructor del proyecto social.
	 * 
	 * @param titulo            Titulo del proyecto social.
	 * @param descripcion       Descripcion del proyecto social.
	 * @param importeSolicitado Importe Solicitado del proyecto social.
	 * @param descripcionSocial Descripcion Social del proyecto social.
	 * @param esNacional boolean para saber si es nacional o no
	 */
	public ProyectoSocial(String titulo, String descripcion, double importeSolicitado, String descripcionSocial,
			boolean esNacional) {
		super(titulo, descripcion, importeSolicitado);
		this.esNacional = esNacional;
		this.descripcionGrupoSocial = descripcionSocial;
	}

	/**
	 * Getter de la descripcion social del proyecto social.
	 * 
	 * @return Descripcion del proyecto social.
	 */
	public String getDescripcionGrupoSocial() {
		return descripcionGrupoSocial;
	}

	/**
	 * Setter de la descrpicion del proyecto social.
	 * 
	 * @param descripcionGrupoSocial Descripcion del proyecto social.
	 */
	public void setDescripcionGrupoSocial(String descripcionGrupoSocial) {
		this.descripcionGrupoSocial = descripcionGrupoSocial;
	}

	/**
	 * Getter de datos estra de un proyecto de tipo
	 * social
	 * 
	 * @return datos extra
	 */
	@Override
	public String getExtraData() {
		return "Extra data";
	}

	/**
	 * Getter de la descripcion de un proyecto de tipo
	 * social
	 * 
	 * @return descripcion del proyecto
	 */
	@Override
	public String getProjectDescription() {
		return this.getDescripcion();
	}

	/**
	 * Getter del tipo un proyecto de tipo
	 * social
	 * 
	 * @return tipo del proyecto
	 */
	@Override
	public ProjectKind getProjectKind() {
		return ProjectKind.Social;
	}

	/**
	 * Getter del titulo de un proyecto de tipo
	 * social
	 * 
	 * @return titulo del proyecto
	 */
	@Override
	public String getProjectTitle() {
		return this.getTitulo();
	}

	/**
	 * Getter de la cantidad de un proyecto de tipo
	 * social
	 * 
	 * @return cantidad que el proyecto ha solicitado
	 */
	@Override
	public double getRequestedAmount() {
		return this.getImporteSolicitado();
	}

	/**
	 * Getter de si un proyecto es 
	 * de tipo nacional o no
	 * 
	 * @return true si es nacional, false si no
	 */
	public boolean isNacional() {
		return esNacional;
	}

	/**
	 * Setter que dira si un proyecto social
	 * es nacional o no.
	 * 
	 * @param nacional variable a settear
	 */
	public void setNacional(boolean nacional) {
		this.esNacional = nacional;
	}	

}

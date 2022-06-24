package Sistemas;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.time.LocalDate;
import java.util.*;
import Colectivos.Colectivo;
import Enumeraciones.TipoEstadoUsuario;
import Usuarios.*;
import es.uam.eps.sadp.grants.InvalidIDException;
import Proyectos.*;

/**
 * Desde esta clase se realizan las modificaciones de la aplicacion, se anaden
 * proyectos, colectivos y usuarios, pero tambien se modifican los estados de
 * los mismos.
 * 
 * @author Diego Cano, Juan Moreno y Julio Carreras.
 * @version 1.6
 * @since 1.1
 *
 */
public class Sistema implements Serializable {
	private static final long serialVersionUID = 6;

	/**
	 * Instancia de nuestro sistema, usado para patron Singleton
	 */
	private static Sistema instancia = null;

	/**
	 * Administrador unico del sistema.
	 */
	private final Usuario admin;

	/**
	 * Lista de usuarios del sistema.
	 */
	private ArrayList<Usuario> usuarios;

	/**
	 * Lista de proyectos del sistema.
	 */
	private ArrayList<Proyecto> proyectos;

	/**
	 * Lista de colectivos del sistema.
	 */
	private ArrayList<Colectivo> colectivos;

	/**
	 * Lista de distritos del sistema.
	 */
	private ArrayList<Distrito> distritos;

	/**
	 * Numero de apoyos que el administrador fijara para que los proyectos sean
	 * financiados.
	 */
	public int apoyosFinanciacion = 0;
	
	/**
	 * fichero de datos donde se guardaran los
	 * datos del sistema
	 */
	private static String data = "data.dat";

	/**
	 * Metodo mediante la cual se obtiene la instancia del sistema actual
	 * @throws InvalidIDException 
	 */
	public synchronized static Sistema getInstancia() throws ClassNotFoundException, IOException, InvalidIDException {
		if (instancia == null) {
			instancia = new Sistema();
		}
		return instancia;
	}

	/**
	 * Constructor privado clase Sistema.
	 * @throws InvalidIDException 
	 */
	private Sistema() throws ClassNotFoundException, IOException, InvalidIDException {
		Path path = Paths.get(data);
		if (Files.exists(path)) {
			load();
			this.admin = new Usuario("admin", "admin", "admin", TipoEstadoUsuario.ADMINISTRADOR);
			return;
		}
		this.usuarios = new ArrayList<Usuario>();
		this.proyectos = new ArrayList<Proyecto>();
		this.colectivos = new ArrayList<Colectivo>();
		this.distritos = new ArrayList<Distrito>();
		this.admin = new Usuario("admin", "admin", "admin", TipoEstadoUsuario.ADMINISTRADOR);
		this.leerDistritos();
	}

	/**
	 * Getter del administrador del sistema.
	 * 
	 * @return administrador Administrador del sistema.
	 */
	public Usuario getAdmin() {
		return admin;
	}

	/**
	 * Getter de los proyectos del sistema
	 * 
	 * @return proyectos Proyectos del sistema.
	 */
	public ArrayList<Proyecto> getProyectos() {
		return proyectos;
	}

	/**
	 * Getter de los usuarios del sistema
	 * 
	 * @return usuarios Usuarios del sistema.
	 */
	public ArrayList<Usuario> getUsuarios() {
		return usuarios;
	}

	/**
	 * Metodo que registra a un usuario en el sistema.
	 * 
	 * @param nombre   Nombre del usuario.
	 * @param NIF      NIF del usuario.
	 * @param password Contrasena del usuario.
	 * 
	 * @return Usuario Usuario registrado en el sistema.
	 */
	public Usuario registrarse(String nombre, String NIF, String password) {
		if (NIF == null || password == null) {
			return null;
		}

		for (Usuario u : usuarios) {
			if (u.getNIF().equals(NIF)) {
				return null;
			}
		}

		Usuario u = new Usuario(nombre, NIF, password);
		this.aniadirUsuario(u);
		return u;
	}

	/**
	 * Getter de los colectivos del sistema
	 * 
	 * @return colectivos Colectivos del sistema.
	 */
	public ArrayList<Colectivo> getColectivos() {
		return colectivos;
	}
	

	/**
	 * Getter de los ditritos del sistema
	 * 
	 * @return distritos Lista de distritos del sistema.
	 */
	public ArrayList<Distrito> getDistritos() {
		return distritos;
	}

	/**
	 * Setter de los distritos del sistema
	 * 
	 * @param distritos lista de distritos del sistema.
	 */
	public void setDistritos(ArrayList<Distrito> distritos) {
		this.distritos = distritos;
	}

	/**
	 * Getter de los apoyos para la financiacion de un proyecto.
	 * @return apoyos para la financiacion.
	 */
	public int getApoyosFinanciacion() {
		return apoyosFinanciacion;
	}

	/**
	 * Setter de los apoyos para la financiacion de un proyecto.
	 * @return apoyosFinanciacion apoyos para la financiacion.
	 */
	public void setApoyosFinanciacion(int apoyosFinanciacion) {
		this.apoyosFinanciacion = apoyosFinanciacion;
	}

	/**
	 * Metodo que permite a un usuario estar logueado en el sistema.
	 * 
	 * @param NIF      NIF del usuario.
	 * @param password Contrasena del usuario.
	 * 
	 * @return Usuario Usuario que ha iniciado sesion en el sistema.
	 * @throws InvalidIDException 
	 * @throws IOException 
	 * @throws ClassNotFoundException 
	 */
	public Usuario logIn(String palabra, String password) throws ClassNotFoundException, IOException, InvalidIDException {
		if (palabra == null || password == null) {
			return null;
		}

		for (Usuario u1 : this.getUsuarios()) {
			if(u1.isLogin() == true) {
				System.out.println("El usuario "+ u1.getNombre() +"esta ya en la aplicacion, intentalo en otro momento");
				return null;
			}
		}
		
		for (Proyecto p : this.getProyectos()) {
			p.actualizarProyecto();
		}
		
		if (palabra.equals("admin") && password.equals("admin")) {
			admin.setLogin(true);
			return admin;
		}

		for (Usuario u2 : usuarios) {
			if ((u2.getNIF().equals(palabra) || (u2.getNombre().equals(palabra))) && u2.getPassword().equals(password)
					&& u2.getEstado().equals(TipoEstadoUsuario.VALIDADO)) {
				u2.setLogin(true);
				return u2;
			}
			
		}
		return null;
	}

	/**
	 * Metodo que servira para cerrar sesion del sistema.
	 * 
	 * @throws IOException            excepcion
	 * @throws ClassNotFoundException excepcion
	 * @throws InvalidIDException excepcion
	 * 
	 */
	public void logOut() throws ClassNotFoundException, IOException, InvalidIDException {
		Usuario usuario = Sistema.getInstancia().usuarioLogin();
		usuario.setLogin(false);
		usuario = null;
		save();
	}
	
	/**
	 * Devuelve el usuario que esta logIn en el sistema si es que lo hay.
	 * @return u Usuario log In.
	 */
	public Usuario usuarioLogin () {
	
		if (this.getAdmin().isLogin() == true) {
			return admin;
		}
		
		for (Usuario u : this.getUsuarios()) {
			if(u.isLogin() == true && u.getEstado() != TipoEstadoUsuario.BLOQUEADO) {
				return u;
			}
		}
		
		return null;
	}

	/**
	 * Metodo que lee el fichero "distritos.txt" y guardara en la lista de distritos
	 * su nombre correspondiente.
	 * 
	 * @throws IOException excepcion.
	 */
	public void leerDistritos() throws IOException {
		try {
			BufferedReader buffer = new BufferedReader(
					new InputStreamReader(new FileInputStream(".." + File.separator + "Tidea" + File.separator + "src"
							+ File.separator + "Testers" + File.separator + "distritos.txt")));

			String linea;

			while ((linea = buffer.readLine()) != null) {
				Distrito d = new Distrito(linea);
				this.aniadirDistrito(d);
			}
			buffer.close();
		}

		catch (Exception e) {
			System.out.println(e);
		}
	}

	/**
	 * Metodo que servira para que un usuario cree y proponga un proyecto de tipo
	 * infraestructura, se anadira a la lista de proyectos del sistema.
	 * 
	 * @param titulo            Titulo del proyecto
	 * @param descr             Descripcion del proyecto
	 * @param importeSolicitado importe que el usuario solicita para ser financiado
	 * @param imagen            Ruta de la imagen del proyecto
	 * @return Proyecto de tipo Infraesructura
	 * @throws ClassNotFoundException excepcion
	 * @throws IOException            excepcion
	 * @throws InvalidIDException 
	 */
	public Proyecto crearProyectoInfraestructura(Usuario proponente, String titulo, String descr,
			double importeSolicitado, String imagen, ArrayList<Distrito> dist)
			throws ClassNotFoundException, IOException, InvalidIDException {
		if (proponente.getEstado() == TipoEstadoUsuario.VALIDADO && proponente.isLogin() == true) {
			if (descr.length() > 500) {
				return null;
			}
			if (titulo.length() > 25) {
				return null;
			}

			/* copia imagenes */

			Path source = Paths.get(imagen); // original file
			Path targetDir = Paths.get("../Tidea/src/Imagenes/Proyectos");

			Files.createDirectories(targetDir);// in case target directory didn't exist

			Path target = targetDir.resolve(titulo + ".jpg");// create new path ending with `name` content
			Files.copy(source, target, StandardCopyOption.REPLACE_EXISTING);
			// I decided to replace already existing files with same name

			ProyectoInfraestructura p = new ProyectoInfraestructura(titulo, descr, importeSolicitado, imagen);
			p.setDistritos(dist);
			p.setUsuarioProponente(proponente);
			p.addVotantes(p.getUsuarioProponente());
			p.setImagen("../Tidea/src/Imagenes/Proyectos" + File.separator + titulo + ".jpg");
			/**
			 * Genera un id para el proyecto a partir del anterior, a no ser que no haya
			 * ninguno que se le pondra el valor 1
			 */
			int numProyectos = (Sistema.getInstancia().getProyectos().size());

			if (numProyectos == 0) {
				p.setId(1);
			} else {
				p.setId((Sistema.getInstancia().getProyectos().get(numProyectos - 1).getId()) + 1);
			}
			p.setApoyosRecibidos(p.getApoyosRecibidos() + 1);
			p.setFechaValidacion(LocalDate.now());
			p.setFechaUltimoVoto(LocalDate.now());
			this.aniadirProyecto(p);
			proponente.addProyectosCreados(p);
			return p;
		}
		return null;
	}

	/**
	 * Metodo que servira para que un usuario cree y proponga un proyecto de tipo
	 * social, se anadira a la lista de proyectos del sistema.
	 * 
	 * @param titulo            Titulo del proyecto.
	 * @param descr             Descripcion del proyecto.
	 * @param importeSolicitado importe que el usuario solicita para ser financiado.
	 * @param descripcionSocial Descripcion social que representa a dicho proyecto.
	 * @param esNacional        Indicara si el proyecto es nacional o no.
	 * @return p Proyecto de tipo Social.
	 * @throws ClassNotFoundException excepcion.
	 * @throws IOException            excepcion.
	 * @throws InvalidIDException 
	 */
	public Proyecto crearProyectoSocial(Usuario proponente, String titulo, String descr, double importeSolicitado,
			String descripcionSocial, boolean esNacional) throws ClassNotFoundException, IOException, InvalidIDException {
		if (proponente.getEstado() == TipoEstadoUsuario.VALIDADO && proponente.isLogin() == true) {
			if (descripcionSocial.length() > 50) {
				return null;
			}
			if (descr.length() > 500) {
				return null;
			}
			if (titulo.length() > 25) {
				return null;
			}

			ProyectoSocial p = new ProyectoSocial(titulo, descr, importeSolicitado, descripcionSocial, esNacional);
			p.setUsuarioProponente(proponente);
			p.addVotantes(p.getUsuarioProponente());
			/**
			 * Genera un id para el proyecto a partir del anterior, a no ser que no haya
			 * ninguno que se le pondra el valor 1.
			 */
			int numProyectos = (Sistema.getInstancia().getProyectos().size());

			if (numProyectos == 0) {
				p.setId(1);
			} else {
				p.setId((Sistema.getInstancia().getProyectos().get(numProyectos - 1).getId()) + 1);
			}

			p.setApoyosRecibidos(p.getApoyosRecibidos() + 1);
			p.setFechaValidacion(LocalDate.now());
			p.setFechaUltimoVoto(LocalDate.now());
			this.aniadirProyecto(p);
			proponente.addProyectosCreados(p);
			return p;
		}
		return null;
	}

	/**
	 * Anade un proyecto a la lista de proyectos del sistema.
	 * 
	 * @param p Proyecto a anadir en el sistema.
	 */
	public void aniadirProyecto(Proyecto p) {
		this.getProyectos().add(p);
	}

	/**
	 * Elimina el proyecto del sistema.
	 * 
	 * @param p Proyecto a eliminar en el sistema.
	 */
	public void eliminarProyecto(Proyecto p) {
		this.getProyectos().remove(p);
	}

	/**
	 * Anade un distrito al sistema.
	 * 
	 * @param d Distrito a anadir al sistema.
	 */
	public void aniadirDistrito(Distrito d) {
		this.getDistritos().add(d);
	}

	/**
	 * Anade un colectivo al sistema.
	 * 
	 * @param c Colectivo a anadir al sistema.
	 */
	public void aniadirColectivo(Colectivo c) {
		this.getColectivos().add(c);
	}

	/**
	 * Anade un usuario al sistema.
	 * 
	 * @param u Usuario a anadir en el sistema.
	 */
	public void aniadirUsuario(Usuario u) {
		this.getUsuarios().add(u);
	}

	/**
	 * Elimina un usuario al sistema.
	 * 
	 * @param u Usuario a eliminar en el sistema.
	 */
	public void eliminarUsuario(Usuario u) {
		this.getUsuarios().remove(u);
	}
	
	/**
	 * Guarda los datos del sistema en un archivo.
	 * 
	 * @param sistema Sistema a guardar
	 */
	public void save() {
		try {
			ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(data));
			oos.writeObject(usuarios);
			oos.writeObject(proyectos);
			oos.writeObject(distritos);
			oos.writeObject(colectivos);
			oos.writeObject(apoyosFinanciacion);
			oos.close();
		} catch (IOException e) {
			e.printStackTrace();
			return;
		}
	}

	/**
	 * Carga en el sistema los datos guardados anterirormente.
	 * 
	 * @param sistema Sistema a cargar
	 * @return Sistema con los datos cargados
	 * @throws ClassNotFoundException excepcion
	 * @throws InvalidIDException 
	 */
	@SuppressWarnings("unchecked")
	public void load() throws ClassNotFoundException, InvalidIDException {
		try {
			ObjectInputStream iobs = new ObjectInputStream(new FileInputStream(data));
			usuarios = (ArrayList<Usuario>) iobs.readObject();
			proyectos = (ArrayList<Proyecto>)iobs.readObject();
			distritos = (ArrayList<Distrito>)iobs.readObject();
			colectivos = (ArrayList<Colectivo>)iobs.readObject();
			apoyosFinanciacion = (int)iobs.readObject();
			iobs.close();	
		} catch (IOException e) {
			e.printStackTrace();
		}
	}


}

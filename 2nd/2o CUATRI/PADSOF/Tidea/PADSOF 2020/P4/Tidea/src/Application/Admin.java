package Application;

import java.awt.BorderLayout;
import java.awt.CardLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.DefaultListModel;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.SwingUtilities;
import javax.swing.border.EmptyBorder;

import Colectivos.Colectivo;
import Enumeraciones.TipoEstadoProyecto;
import Enumeraciones.TipoEstadoUsuario;
import Proyectos.Proyecto;
import Sistemas.Sistema;
import Usuarios.Usuario;
import es.uam.eps.sadp.grants.InvalidIDException;
/**
 * clase que implementa toda la interfaz del administrador.
 * @author Juan Moreno, Julio Carreras y Diego Cano
 * @version 1.8
 * @since 1.1
 */
public class Admin extends JFrame {

	/**
	 * Serial version UID
	 */
	private static final long serialVersionUID = 1L;

	/** Declaramos botones que vayamos a utilizar */
	private JButton proyectos;
	private JButton usuarios;
	private JButton usuariosbloqueados;
	private JButton colectivos;
	private JButton proyectosPendientes;
	private JButton usuariosPendientes;
	private JButton logOut;
	private JButton goBackButton;
	private JButton bloquear;
	private JButton desbloquear;
	private JButton aceptar;
	private JButton rechazar;

	/** declaramos listas para la gesti�n de usuarios y proyectos */
	private JList<Usuario> noBloqueados;
	private JList<Usuario> bloqueados;
	private JList<Proyecto> listaProyectos;
	private JList<Colectivo> listaColectivos;
	private JList<Proyecto> proyectosPendienteslist;
	private JList<Usuario> usuariosPendienteslist;

	/** declaramos listas auxiliares para la gesti�n de usuarios y proyectos */
	private DefaultListModel<Usuario> defaultUsuarios;
	private DefaultListModel<Usuario> defaultBloqueados;
	private DefaultListModel<Proyecto> defaultProyectos;
	private DefaultListModel<Colectivo> defaultColectivos;
	private DefaultListModel<Proyecto> defaultProyectospendientes;
	private DefaultListModel<Usuario> defaultUsuariospendientes;

	/**
	 * Variable donde se gaudar� el usuario admin que previamente habr� iniciado
	 * sesi�n
	 */
	private Usuario admin;

	/**
	 * Panel de inicio del administrador
	 * @param cardlayout Controlador de que paneles se muestran.
	 * @param contentPane Panel en el que esta cntenido.
	 * @return Penel de inicio del administrador
	 * @throws ClassNotFoundException excepcion.
	 * @throws IOException excepcion.
	 * @throws InvalidIDException excepcion.
	 */
	public JPanel HomeAdmin(CardLayout cardlayout, Container contentPane)
			throws ClassNotFoundException, IOException, InvalidIDException {
		/**
		 * Sistema global
		 */
		final Sistema sistema;
		sistema = Sistema.getInstancia();
		admin = sistema.logIn("admin", "admin");
		
		/** Labels para el logo de la aplicaci�n y el mensaje de bienvenida */
		JLabel picLabel = new JLabel(new ImageIcon(ImageIO.read(new File(".." + File.separator + "Tidea"
				+ File.separator + "src" + File.separator + "Application" + File.separator + "logo.jpeg"))));
		JLabel welcome = new JLabel("Bienvenido " + sistema.usuarioLogin().getNIF() + "!");
		welcome.setFont(new Font("Arial", Font.BOLD, 24));
		welcome.setHorizontalAlignment(SwingConstants.RIGHT);

		/**Label para los apoyos de financiacion de un proyecto*/
		JLabel apoyosFinanciacion = new JLabel(
				"Apoyos para poder solicitar financiacion: " + sistema.apoyosFinanciacion);
		apoyosFinanciacion.setFont(new Font("Arial", Font.BOLD, 16));
		JTextField textField = new JTextField(10);

		textField.setMaximumSize(new Dimension(300, 20));
		apoyosFinanciacion.setLabelFor(textField);
		JButton asignar = new JButton("Asignar");
		asignar.setMaximumSize(new Dimension(90, 25));
		asignar.setFont(new Font("Arial", Font.PLAIN, 16));

		/** panel a devolver */
		JPanel jp = new JPanel();
		jp.setName("Tidea");
		jp.setLayout(new BorderLayout());

		/** panel para ajustar elementos a la izquierda */
		JPanel jpL = new JPanel();
		jpL.setLayout(new BoxLayout(jpL, BoxLayout.Y_AXIS));
		jpL.setBorder(new EmptyBorder(50, 10, 10, 10));

		/** panel para ajustar elementos al centro */
		JPanel jpC = new JPanel();
		jpC.setLayout(new BoxLayout(jpC, BoxLayout.X_AXIS));
		jpC.setBorder(new EmptyBorder(50, 10, 10, 10));

		/** creaci�n y personalizaci�n de botones de este panel */
		
		/**Usuarios */
		usuarios = new JButton("Usuarios");
		usuarios.setBackground(new Color(150, 255, 150));
		usuarios.setMaximumSize(new Dimension(100, 35));
		usuarios.setFont(new Font("Arial", Font.PLAIN, 16));
		/**Usuarios bloqueados*/
		usuariosbloqueados = new JButton("Usuarios Bloqueados");
		usuariosbloqueados.setBackground(new Color(150, 255, 150));
		usuariosbloqueados.setMaximumSize(new Dimension(200, 35));
		usuariosbloqueados.setFont(new Font("Arial", Font.PLAIN, 16));
		/**Proyectos*/
		proyectos = new JButton("Proyectos");
		proyectos.setBackground(new Color(150, 255, 150));
		proyectos.setMaximumSize(new Dimension(125, 35));
		proyectos.setFont(new Font("Arial", Font.PLAIN, 16));
		/**Colectivos*/
		colectivos = new JButton("Colectivos");
		colectivos.setBackground(new Color(150, 255, 150));
		colectivos.setMaximumSize(new Dimension(125, 35));
		colectivos.setFont(new Font("Arial", Font.PLAIN, 16));
		/**Boton de logout*/
		logOut = new JButton("Cerrar Sesi�n");
		logOut.setBackground(new Color(150, 255, 150));
		logOut.setMaximumSize(new Dimension(150, 35));
		logOut.setFont(new Font("Arial", Font.PLAIN, 16));
		/**Proyectos pendientes de validar*/
		proyectosPendientes = new JButton("Proyectos Pendientes");
		proyectosPendientes.setFont(new Font("Arial", Font.PLAIN, 26));
		proyectosPendientes.setBackground(new Color(150, 255, 150));
		proyectosPendientes.setMaximumSize(new Dimension(300, 70));
		/**Usuarios pendientes de validar*/
		usuariosPendientes = new JButton("Usuarios pendientes");
		usuariosPendientes.setFont(new Font("Arial", Font.PLAIN, 26));
		usuariosPendientes.setBackground(new Color(150, 255, 150));
		usuariosPendientes.setMaximumSize(new Dimension(300, 70));

		/** a�adir los botones en los paneles que queremos */

		jpL.add(welcome);
		jpL.add(Box.createRigidArea(new Dimension(15, 15)));
		jpL.add(apoyosFinanciacion);
		jpL.add(Box.createRigidArea(new Dimension(15, 5)));
		jpL.add(textField);
		jpL.add(Box.createRigidArea(new Dimension(15, 5)));
		jpL.add(asignar);
		jpL.add(Box.createRigidArea(new Dimension(15, 15)));
		jpL.add(usuarios);
		jpL.add(Box.createRigidArea(new Dimension(15, 15)));
		jpL.add(usuariosbloqueados);
		jpL.add(Box.createRigidArea(new Dimension(15, 15)));
		jpL.add(proyectos);
		jpL.add(Box.createRigidArea(new Dimension(15, 15)));
		jpL.add(colectivos);
		jpL.add(Box.createRigidArea(new Dimension(15, 15)));
		jpL.add(logOut);

		jpC.add(Box.createRigidArea(new Dimension(200, 0)));
		jpC.add(proyectosPendientes);
		jpC.add(Box.createRigidArea(new Dimension(30, 0)));
		jpC.add(usuariosPendientes);

		jp.add(jpC, BorderLayout.CENTER);
		jp.add(jpL, BorderLayout.WEST);
		jp.add(picLabel, BorderLayout.NORTH);

		/**Accion para apoyos de financiacion.*/
		asignar.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				String numero = textField.getText();
				int parseado = Integer.parseInt(numero);
				sistema.setApoyosFinanciacion(parseado);
			}
		});

		/**Accion para mostrar lista de usuarios.*/
		usuarios.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Usuarios");
			}
		});

		/**Accion para mostrar usuarios bloqueados*/
		usuariosbloqueados.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Usuarios Bloqueados");
			}
		});

		/**Accion para ver la lista de proyectos*/
		proyectos.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Proyectos");
			}
		});

		/**Accion para ver la lista de colectivos.*/
		colectivos.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Colectivos");
			}
		});

		/**Accion para ver la lista de proyectos que estan pendientes de validar*/
		proyectosPendientes.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Proyectos Pendientes");
			}
		});

		/**Accion para ver la lista de los usuarios pendientes de validar*/
		usuariosPendientes.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Usuarios Pendientes");
			}
		});

		/**Accion para cerrar sesion*/
		logOut.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				try {
					sistema.logOut();
					JFrame topFrame = (JFrame) SwingUtilities.getWindowAncestor(jp);
					topFrame.dispose();
					new App();

				} catch (ClassNotFoundException | IOException e1) {
					e1.printStackTrace();
				}
				/* falta ir al panel de LogIn desde aqui */ catch (Exception e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			}
		});

		/**Modifica el tamano y la visibilidad*/
		jp.setVisible(true);
		jp.setSize(300, 300);

		return jp;
	}

	/**
	 * Penel para mostrar la lista de usuarios al administrador.
	 * @param cardlayout controla la visibilidad del panel
	 * @param contentPane Panel en el que esta contenido
	 * @return panel de usuarios.
	 * @throws ClassNotFoundException excepcion.
	 * @throws IOException excepcion.
	 * @throws InvalidIDException excepcion.
	 */
	public JPanel usuarios(CardLayout cardlayout, Container contentPane)
			throws ClassNotFoundException, IOException, InvalidIDException {
		/** panel a devolver */
		JPanel jp = new JPanel();
		jp.setName("Tidea");
		jp.setLayout(new BorderLayout());

		/**Sistema global*/
		final Sistema sistema;
		sistema = Sistema.getInstancia();

		/** lista para poder bloquear usuarios */
		defaultUsuarios = new DefaultListModel<Usuario>();
		populateUsuarios();
		noBloqueados = new JList<Usuario>(defaultUsuarios);
		noBloqueados.setFont(new Font("Arial", Font.PLAIN, 16));
		noBloqueados.setFixedCellHeight(25);

		/** panel para ajustar elementos a la izquierda */
		JPanel jpL = new JPanel();
		jpL.setLayout(new BoxLayout(jpL, BoxLayout.Y_AXIS));
		jpL.setBorder(new EmptyBorder(50, 10, 10, 10));

		/**Panel BoxLayout para ponerlo en una sola columna o fila*/
		JPanel jpS = new JPanel();
		jpL.setLayout(new BoxLayout(jpL, BoxLayout.X_AXIS));
		jpL.setBorder(new EmptyBorder(50, 10, 10, 10));

		/**
		 * boton para ir hacia atr�s (HomeAdmin) y para bloquear un usuarui que hemos
		 * seleccionado de la lista
		 */
		goBackButton = new JButton(new ImageIcon(ImageIO.read(new File(".." + File.separator + "Tidea" + File.separator
				+ "src" + File.separator + "Application" + File.separator + "goback.png"))));
		bloquear = new JButton("Bloquear Usuario");
		bloquear.setBackground(new Color(150, 255, 150));
		bloquear.setMaximumSize(new Dimension(225, 250));
		bloquear.setFont(new Font("Arial", Font.PLAIN, 28));

		/**Anadimos los botones*/
		jpL.add(goBackButton);
		jp.add(jpL, BorderLayout.WEST);
		jpS.add(bloquear);
		jp.add(jpS, BorderLayout.SOUTH);
		jp.add(noBloqueados);

		/**Accion para ir hacia atras*/
		goBackButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				cardlayout.first(contentPane);
			}
		});

		/**Accion para quitar usuarios y ponerlos en bloqueados si todo marcha correctamente*/
		bloquear.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				try {
					if (noBloqueados.getSelectedValue() == null) {
						JOptionPane.showMessageDialog(jp, "Debes seleccionar un usuario para poder bloquearlo", "Error",
								JOptionPane.ERROR_MESSAGE);
						return;
					}
					/*
					 * bloqueamos el usuario que hemos seleccionado, lo movemos a la lista de
					 * bloqueados y lo eliminamos de la lista de usuarios
					 */
					sistema.usuarioLogin().bloquearUsuario(noBloqueados.getSelectedValue());
					if (noBloqueados.getSelectedValue().getEstado().equals(TipoEstadoUsuario.BLOQUEADO)) {
						defaultBloqueados.addElement(noBloqueados.getSelectedValue());
						defaultUsuarios.removeElement(noBloqueados.getSelectedValue());
					}
				} catch (ClassNotFoundException | IOException | InvalidIDException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			}
		});

		/**Cambiamos la visivilidad y el tamano*/
		jp.setVisible(true);
		jp.setSize(300, 300);

		return jp;
	}

	/**
	 * m�todo para poblar la lista de usuarios que se puede bloquear en el sistema
	 * @throws ClassNotFoundException excepcion.
	 * @throws IOException excepcion.
	 * @throws InvalidIDException excepcion.
	 */
	public void populateUsuarios() throws ClassNotFoundException, IOException, InvalidIDException {
		final Sistema sistema;
		sistema = Sistema.getInstancia();
		for (Usuario u : sistema.getUsuarios()) {
			defaultUsuarios.addElement(u);
		}
	}

	/**
	 * Panel que muestra la lista de usuario bloqueados por el administrador.
	 * @param cardlayout controla la visibilidad del panel
	 * @param contentPane Panel en el que esta contenido
	 * @return panel de usuarios bloqueados.
	 * @throws ClassNotFoundException excepcion.
	 * @throws IOException excepcion.
	 * @throws InvalidIDException excepcion.
	 */
	public JPanel usuariosBloqueados(CardLayout cardlayout, Container contentPane)
			throws ClassNotFoundException, IOException, InvalidIDException {
		
		/** panel a devolver */
		JPanel jp = new JPanel();
		jp.setName("Tidea");
		jp.setLayout(new BorderLayout());

		/**Sistema global*/
		final Sistema sistema;
		sistema = Sistema.getInstancia();

		/**Usuarios bloqueados*/
		defaultBloqueados = new DefaultListModel<Usuario>();
		populateBloqueados();
		bloqueados = new JList<Usuario>(defaultBloqueados);
		bloqueados.setFont(new Font("Arial", Font.PLAIN, 16));
		bloqueados.setFixedCellHeight(25);

		/**BoxLayout para que se muestren en una lista vertical*/
		JPanel jpL = new JPanel();
		jpL.setLayout(new BoxLayout(jpL, BoxLayout.Y_AXIS));
		jpL.setBorder(new EmptyBorder(50, 10, 10, 10));
		
		/**BoxLayout para que se muestren en una lista horizontal*/
		JPanel jpS = new JPanel();
		jpL.setLayout(new BoxLayout(jpL, BoxLayout.X_AXIS));
		jpL.setBorder(new EmptyBorder(50, 10, 10, 10));

		/**Anadimos los botones correspondientes*/
		
		/**Boton de volver atras*/
		goBackButton = new JButton(new ImageIcon(ImageIO.read(new File(".." + File.separator + "Tidea" + File.separator
				+ "src" + File.separator + "Application" + File.separator + "goback.png"))));
		
		/**Boton de desbloquear*/
		desbloquear = new JButton("Desbloquear Usuario");
		desbloquear.setBackground(new Color(150, 255, 150));
		desbloquear.setMaximumSize(new Dimension(225, 250));
		desbloquear.setFont(new Font("Arial", Font.PLAIN, 28));

		/**Anadimos botones al panel*/
		jpL.add(goBackButton);
		jp.add(jpL, BorderLayout.WEST);
		jpS.add(desbloquear);
		jp.add(jpS, BorderLayout.SOUTH);
		jp.add(bloqueados);

		/**Accion para mostrar el primer panel*/
		goBackButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				cardlayout.first(contentPane);
			}
		});

		/**Accion para desbloquear un usuario*/
		desbloquear.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				try {
					if (bloqueados.getSelectedValue() == null) {
						JOptionPane.showMessageDialog(jp, "Debes seleccionar un usuario para poder desbloquearlo",
								"Error", JOptionPane.ERROR_MESSAGE);
						return;
					}
					sistema.usuarioLogin().desbloquearUsuario(bloqueados.getSelectedValue());
					if (bloqueados.getSelectedValue().getEstado().equals(TipoEstadoUsuario.VALIDADO)) {
						defaultBloqueados.removeElement(bloqueados.getSelectedValue());
					}
				} catch (ClassNotFoundException | IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			}
		});

		/**Modificamos la visibilidad y el tamano de la pantalla*/
		jp.setVisible(true);
		jp.setSize(300, 300);

		return jp;
	}

	/** Metodo que obtiene los usuarios bloqueados.
	 * 
	 * @throws ClassNotFoundException excepcion.
	 * @throws IOException excepcion.
	 * @throws InvalidIDException excepcion.
	 */
	public void populateBloqueados() throws ClassNotFoundException, IOException, InvalidIDException {
		final Sistema sistema;
		sistema = Sistema.getInstancia();
		for (Usuario u : sistema.getUsuarios()) {
			if (u.getEstado().equals(TipoEstadoUsuario.BLOQUEADO))
				defaultBloqueados.addElement(u);
		}

	}

	/**
	 * Metodo que muestra los proyectos del sistema. 
	 * @param cardlayout controla la visibilidad del panel
	 * @param contentPane Panel en el que esta contenido
	 * @return panel de proyectos.
	 * @throws ClassNotFoundException excepcion.
	 * @throws IOException excepcion.
	 * @throws InvalidIDException excepcion.
	 */
	public JPanel proyectos(CardLayout cardlayout, Container contentPane)
			throws ClassNotFoundException, IOException, InvalidIDException {
		
		/** panel a devolver */
		JPanel jp = new JPanel();
		jp.setName("Tidea");
		jp.setLayout(new BorderLayout());

		/** lista de proyectos del sistema */
		defaultProyectos = new DefaultListModel<Proyecto>();
		populateProyectos();
		listaProyectos = new JList<Proyecto>(defaultProyectos);
		listaProyectos.setFont(new Font("Arial", Font.PLAIN, 16));
		listaProyectos.setFixedCellHeight(25);

		/**BoxLayout para que se muestren en una lista vertical*/
		JPanel jpL = new JPanel();
		jpL.setLayout(new BoxLayout(jpL, BoxLayout.Y_AXIS));
		jpL.setBorder(new EmptyBorder(50, 10, 10, 10));

		/**Anadimos los botones correspondientes*/
		
		/**Boton de volver atras*/
		goBackButton = new JButton(new ImageIcon(ImageIO.read(new File(".." + File.separator + "Tidea" + File.separator
				+ "src" + File.separator + "Application" + File.separator + "goback.png"))));

		/**Anadimos botones al panel*/
		jpL.add(goBackButton);
		jp.add(jpL, BorderLayout.WEST);
		jp.add(listaProyectos);

		/**Accion para cambiar de panel y volver atras*/
		goBackButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				cardlayout.first(contentPane);
			}
		});

		/**Modificamos la visibilidad y el tamano de la pantalla*/
		jp.setVisible(true);
		jp.setSize(300, 300);

		return jp;
	}

	/** Metodo que obtiene los proyectos del sistema.
	 * 
	 * @throws ClassNotFoundException excepcion.
	 * @throws IOException excepcion.
	 * @throws InvalidIDException excepcion.
	 */
	public void populateProyectos() throws ClassNotFoundException, IOException, InvalidIDException {
		final Sistema sistema;
		sistema = Sistema.getInstancia();
		for (Proyecto p : sistema.getProyectos()) {
			if (p.getEstadoProyecto().equals(TipoEstadoProyecto.VALIDADO)) {
				defaultProyectos.addElement(p);
			}
		}
	}

	/**
	 * Metodo que muestra los colectivos del sistema.
	 * @param cardlayout controla la visibilidad del panel
	 * @param contentPane Panel en el que esta contenido
	 * @return panel de coelctivos.
	 * @throws ClassNotFoundException excepcion.
	 * @throws IOException excepcion.
	 */
	public JPanel colectivos(CardLayout cardlayout, Container contentPane)
			throws ClassNotFoundException, IOException, InvalidIDException {
		
		/** panel a devolver */
		JPanel jp = new JPanel();
		jp.setName("Tidea");
		jp.setLayout(new BorderLayout());

		/**Anadimos los botones correspondientes*/
		
		/** lista de colectivos del sistema */
		defaultColectivos = new DefaultListModel<Colectivo>();
		populateColectivos();
		listaColectivos = new JList<Colectivo>(defaultColectivos);
		listaColectivos.setFont(new Font("Arial", Font.PLAIN, 16));
		listaColectivos.setFixedCellHeight(25);

		/**BoxLayout para que se muestren en una lista vertical*/
		JPanel jpL = new JPanel();
		jpL.setLayout(new BoxLayout(jpL, BoxLayout.Y_AXIS));
		jpL.setBorder(new EmptyBorder(50, 10, 10, 10));
		
		/**Boton de volver atras*/
		goBackButton = new JButton(new ImageIcon(ImageIO.read(new File(".." + File.separator + "Tidea" + File.separator
				+ "src" + File.separator + "Application" + File.separator + "goback.png"))));

		/**Anadimos botones al panel*/
		jpL.add(goBackButton);
		jp.add(jpL, BorderLayout.WEST);
		jp.add(listaColectivos);

		/**Accion para cambiar de panel y volver atras*/
		goBackButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				cardlayout.first(contentPane);
			}
		});

		/**Modificamos la visibilidad y el tamano de la pantalla*/
		jp.setVisible(true);
		jp.setSize(300, 300);

		return jp;
	}

	/** Metodo que obtiene los colectivos del sistema.
	 * 
	 * @throws ClassNotFoundException excepcion.
	 * @throws IOException excepcion.
	 * @throws InvalidIDException excepcion.
	 */
	public void populateColectivos() throws ClassNotFoundException, IOException, InvalidIDException {
		final Sistema sistema;
		sistema = Sistema.getInstancia();
		for (Colectivo c : sistema.getColectivos()) {
			defaultColectivos.addElement(c);
		}
	}

	/**
	 * Metodo que muestra los proyectos pendientes del sistema.
	 * @param cardlayout controla la visibilidad del panel
	 * @param contentPane Panel en el que esta contenido
	 * @return panel de proyectos pendientes.
	 * @throws ClassNotFoundException excepcion.
	 * @throws IOException excepcion.
	 */
	public JPanel proyectosPendientes(CardLayout cardlayout, Container contentPane)
			throws ClassNotFoundException, IOException, InvalidIDException {
		
		/** panel a devolver */
		JPanel jp = new JPanel();
		jp.setName("Tidea");
		jp.setLayout(new BorderLayout());

		/**Anadimos los botones correspondientes*/
		
		/** lista de proyectos pendientes de aceptar en el sistema */
		defaultProyectospendientes = new DefaultListModel<Proyecto>();
		populateProyectosPendientes();
		proyectosPendienteslist = new JList<Proyecto>(defaultProyectospendientes);
		proyectosPendienteslist.setFont(new Font("Arial", Font.PLAIN, 16));
		proyectosPendienteslist.setFixedCellHeight(25);

		/**Boton de motivo de rechazo*/
		JTextField motivo = new JTextField(50);
		motivo.setMaximumSize(new Dimension(70, 50));
		JLabel textomotivo = new JLabel("Motivo: ");
		textomotivo.setFont(new Font("Arial", Font.PLAIN, 20));

		/**BoxLayout para que se muestren en una lista vertical*/
		JPanel jpL = new JPanel();
		jpL.setLayout(new BoxLayout(jpL, BoxLayout.Y_AXIS));
		jpL.setBorder(new EmptyBorder(50, 10, 10, 10));

		/**BoxLayout para que se muestren en una lista horizontal*/
		JPanel jpS = new JPanel();
		jpS.setLayout(new BoxLayout(jpS, BoxLayout.X_AXIS));
		jpS.setBorder(new EmptyBorder(50, 10, 10, 10));

		goBackButton = new JButton(new ImageIcon(ImageIO.read(new File(".." + File.separator + "Tidea" + File.separator
				+ "src" + File.separator + "Application" + File.separator + "goback.png"))));
		aceptar = new JButton("Aceptar");
		aceptar.setBackground(new Color(150, 255, 150));
		aceptar.setMaximumSize(new Dimension(150, 100));
		aceptar.setFont(new Font("Arial", Font.PLAIN, 20));
		rechazar = new JButton("Rechazar");
		rechazar.setBackground(new Color(150, 255, 150));
		rechazar.setMaximumSize(new Dimension(150, 100));
		rechazar.setFont(new Font("Arial", Font.PLAIN, 20));

		/**Boton de volver atras*/
		jpL.add(goBackButton);
		jpS.add(Box.createRigidArea(new Dimension(500, 0)));
		
		/**Anadimos los botones al panel*/
		jpS.add(aceptar);
		jpS.add(Box.createRigidArea(new Dimension(15, 15)));
		jpS.add(textomotivo);
		jpS.add(motivo);
		jpS.add(rechazar);

		/**Anadimos botones a las distintas areas*/
		jp.add(jpL, BorderLayout.WEST);
		jp.add(jpS, BorderLayout.SOUTH);
		jp.add(proyectosPendienteslist, BorderLayout.CENTER);

		/**Accion para cambiar de panel y volver atras*/
		goBackButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				cardlayout.first(contentPane);
			}
		});

		/**Accion para aceptar un proyecto*/
		aceptar.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				try {
					if (proyectosPendienteslist.getSelectedValue() == null) {
						JOptionPane.showMessageDialog(jp, "Debes seleccionar un proyecto para poder aceptarlo", "Error",
								JOptionPane.ERROR_MESSAGE);
						return;
					}
					proyectosPendienteslist.getSelectedValue().aprobarProyecto();
					if (proyectosPendienteslist.getSelectedValue().getEstadoProyecto()
							.equals(TipoEstadoProyecto.VALIDADO)) {
						defaultProyectos.addElement(proyectosPendienteslist.getSelectedValue());
						defaultProyectospendientes.removeElement(proyectosPendienteslist.getSelectedValue());
					}
				} catch (ClassNotFoundException | IOException e1) {
					e1.printStackTrace();
				} catch (InvalidIDException e1) {
					e1.printStackTrace();
				}
			}
		});

		/**Accion para rechazar un proyecto*/
		rechazar.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				try {
					/* poner que se abra un cuadro de dexto para indicar la razon del rechazo */
					if (proyectosPendienteslist.getSelectedValue() == null) {
						JOptionPane.showMessageDialog(jp, "Debes seleccionar un proyecto para poder rechazarlo",
								"Error", JOptionPane.ERROR_MESSAGE);
						return;
					}
					if (motivo.getText().equals("")) {
						JOptionPane.showMessageDialog(jp, "Debes indicar un motivo al rechazar el proyecto", "Error",
								JOptionPane.ERROR_MESSAGE);
						return;
					}
					proyectosPendienteslist.getSelectedValue().rechazarProyecto(motivo.getText());
					if (proyectosPendienteslist.getSelectedValue().getEstadoProyecto()
							.equals(TipoEstadoProyecto.RECHAZADO)) {
						defaultProyectospendientes.removeElement(proyectosPendienteslist.getSelectedValue());
					}
				} catch (ClassNotFoundException | IOException e1) {
					e1.printStackTrace();
				} catch (InvalidIDException e1) {
					e1.printStackTrace();
				}
			}
		});

		/**Modificamos la visibilidad y el tamano de la pantalla*/
		jp.setVisible(true);
		jp.setSize(300, 300);

		return jp;
	}

	/** Metodo que obtiene los proyectos pendientes del sistema.
	 * 
	 * @throws ClassNotFoundException excepcion.
	 * @throws IOException excepcion.
	 * @throws InvalidIDException excepcion.
	 */
	public void populateProyectosPendientes() throws ClassNotFoundException, IOException, InvalidIDException {
		final Sistema sistema;
		sistema = Sistema.getInstancia();
		for (Proyecto p : sistema.getProyectos()) {
			if (p.getEstadoProyecto().equals(TipoEstadoProyecto.PENDIENTEVALIDACION)) {
				defaultProyectospendientes.addElement(p);
			}
		}
	}

	/**
	 * Metodo que muestra los usuarios pendientes del sistema.
	 * @param cardlayout controla la visibilidad del panel
	 * @param contentPane Panel en el que esta contenido
	 * @return panel de usuarios pendientes.
	 * @throws ClassNotFoundException excepcion.
	 * @throws IOException excepcion.
	 */
	public JPanel usuariosPendientes(CardLayout cardlayout, Container contentPane)
			throws ClassNotFoundException, IOException, InvalidIDException {
		
		/** panel a devolver */
		JPanel jp = new JPanel();
		jp.setName("Tidea");
		jp.setLayout(new BorderLayout());

		/**Anadimos los botones correspondientes*/
		
		/** lista de usuarios pendientes de aceptar en el sistema */
		defaultUsuariospendientes = new DefaultListModel<Usuario>();
		populateUsuariosPendientes();
		usuariosPendienteslist = new JList<Usuario>(defaultUsuariospendientes);
		usuariosPendienteslist.setFont(new Font("Arial", Font.PLAIN, 16));
		usuariosPendienteslist.setFixedCellHeight(25);

		/**BoxLayout para que se muestren en una lista vertical*/
		JPanel jpL = new JPanel();
		jpL.setLayout(new BoxLayout(jpL, BoxLayout.Y_AXIS));
		jpL.setBorder(new EmptyBorder(50, 10, 10, 10));

		/**BoxLayout para que se muestren en una lista horizontal*/
		JPanel jpS = new JPanel();
		jpS.setLayout(new BoxLayout(jpS, BoxLayout.X_AXIS));
		jpS.setBorder(new EmptyBorder(50, 10, 10, 10));

		/**Boton de volver atras*/
		goBackButton = new JButton(new ImageIcon(ImageIO.read(new File(".." + File.separator + "Tidea" + File.separator
				+ "src" + File.separator + "Application" + File.separator + "goback.png"))));
		
		/**Boton para aceptar*/
		aceptar = new JButton("Aceptar");
		aceptar.setBackground(new Color(150, 255, 150));
		aceptar.setMaximumSize(new Dimension(150, 100));
		aceptar.setFont(new Font("Arial", Font.PLAIN, 20));
		
		/**Boton para rechazar*/
		rechazar = new JButton("Rechazar");
		rechazar.setBackground(new Color(150, 255, 150));
		rechazar.setMaximumSize(new Dimension(150, 100));
		rechazar.setFont(new Font("Arial", Font.PLAIN, 20));

		/**Anadimos los botones al panel*/
		jpL.add(goBackButton);
		jpS.add(Box.createRigidArea(new Dimension(500, 0)));
		jpS.add(aceptar);
		jpS.add(Box.createRigidArea(new Dimension(15, 15)));
		jpS.add(rechazar);
		jp.add(jpL, BorderLayout.WEST);
		jp.add(jpS, BorderLayout.SOUTH);
		jp.add(usuariosPendienteslist, BorderLayout.CENTER);

		/**Accion para cambiar de panel y volver atras*/
		goBackButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				cardlayout.first(contentPane);
			}
		});

		/**Accion para aceptar un usuario*/
		aceptar.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				try {
					if (usuariosPendienteslist.getSelectedValue() == null) {
						JOptionPane.showMessageDialog(jp, "Debes seleccionar un usuario para poder aceptarlo", "Error",
								JOptionPane.ERROR_MESSAGE);
						return;
					}
					admin.validarUsuario(usuariosPendienteslist.getSelectedValue());
					if (usuariosPendienteslist.getSelectedValue().getEstado().equals(TipoEstadoUsuario.VALIDADO)) {
						defaultUsuariospendientes.removeElement(usuariosPendienteslist.getSelectedValue());
					}
				} catch (ClassNotFoundException | IOException e1) {
					e1.printStackTrace();
				} catch (InvalidIDException e1) {
					e1.printStackTrace();
				}
			}
		});

		/**Accion para rechar un usuario*/
		rechazar.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				try {
					if (usuariosPendienteslist.getSelectedValue() == null) {
						JOptionPane.showMessageDialog(jp, "Debes seleccionar un usuario para poder rechazarlo", "Error",
								JOptionPane.ERROR_MESSAGE);
						return;
					}
					admin.rechazarUsuario(usuariosPendienteslist.getSelectedValue());
					if (usuariosPendienteslist.getSelectedValue().getEstado().equals(TipoEstadoUsuario.RECHAZADO)) {
						defaultUsuariospendientes.removeElement(usuariosPendienteslist.getSelectedValue());
					}
				} catch (ClassNotFoundException | IOException e1) {
					e1.printStackTrace();
				} catch (InvalidIDException e1) {
					e1.printStackTrace();
				}
			}
		});

		/**Modificamos la visibilidad y el tamano de la pantalla*/
		jp.setVisible(true);
		jp.setSize(300, 300);

		return jp;
	}

	/** Metodo que obtiene los usuarios pendientes del sistema.
	 * 
	 * @throws ClassNotFoundException excepcion.
	 * @throws IOException excepcion.
	 * @throws InvalidIDException excepcion.
	 */
	public void populateUsuariosPendientes() throws ClassNotFoundException, IOException, InvalidIDException {
		final Sistema sistema;
		sistema = Sistema.getInstancia();
		for (Usuario u : sistema.getUsuarios()) {
			if (u.getEstado().equals(TipoEstadoUsuario.PENDIENTEVALIDAR)) {
				defaultUsuariospendientes.addElement(u);
			}
		}
	}

	/**
	 * Llama a todos los metodos en los aue se crean los diferentes paneles para
	 * la visibilidad del administrador.
	 * @throws Exception excepcion.
	 */
	public Admin() throws Exception {
		super("Tidea");

		final CardLayout cardlayout = new CardLayout();

		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setSize(1280, 720);
		this.setVisible(true);

		final Container contentPane = this.getContentPane();
		contentPane.setLayout(cardlayout);

		final JPanel HomeAdmin = this.HomeAdmin(cardlayout, contentPane);
		final JPanel tablaUsuarios = this.usuarios(cardlayout, contentPane);
		final JPanel tablaProyectos = this.proyectos(cardlayout, contentPane);
		final JPanel tablaColectivos = this.colectivos(cardlayout, contentPane);
		final JPanel proyectosPendientes = this.proyectosPendientes(cardlayout, contentPane);
		final JPanel usuariosPendientes = this.usuariosPendientes(cardlayout, contentPane);
		final JPanel usuariosBloqueados = this.usuariosBloqueados(cardlayout, contentPane);

		contentPane.setPreferredSize(new Dimension(1280, 720));
		contentPane.add(HomeAdmin, "Inicio Admin");
		contentPane.add(tablaUsuarios, "Usuarios");
		contentPane.add(tablaProyectos, "Proyectos");
		contentPane.add(tablaColectivos, "Colectivos");
		contentPane.add(proyectosPendientes, "Proyectos Pendientes");
		contentPane.add(usuariosPendientes, "Usuarios Pendientes");
		contentPane.add(usuariosBloqueados, "Usuarios Bloqueados");

		this.pack();
		this.setLocationRelativeTo(null);
		this.setResizable(true);
	}

	/**
	 * Metodo que cargar la parte del administrador llamando al metodo Admin()
	 * @param args argumentos de entrada.
	 * @throws Exception excepcion.
	 */
	public static void main(String[] args) throws Exception {
		new Admin();
	}

}

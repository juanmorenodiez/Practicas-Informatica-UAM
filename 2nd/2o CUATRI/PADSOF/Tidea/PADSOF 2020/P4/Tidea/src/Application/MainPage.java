package Application;

import java.awt.BorderLayout;
import java.awt.CardLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.HeadlessException;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

import javax.imageio.ImageIO;
import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.BoxLayout;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;
import javax.swing.SwingConstants;
import javax.swing.SwingUtilities;
import javax.swing.border.EmptyBorder;
import javax.swing.border.LineBorder;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.JTableHeader;

import Application.App;
import Colectivos.Colectivo;
import Enumeraciones.TipoEstadoProyecto;
import Notificaciones.Notificacion;
import Proyectos.*;
import Sistemas.Sistema;
import Usuarios.Distrito;
import Usuarios.Usuario;
import es.uam.eps.sadp.grants.GrantRequest.ProjectKind;
import es.uam.eps.sadp.grants.InvalidIDException;
import es.uam.eps.sadp.grants.InvalidRequestException;

public class MainPage extends JFrame {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	/* Declaramos botones que vayamos a utilizar */
	private JButton proyectos;
	private JButton home;
	private JButton misproyectos;
	private JButton colectivos;
	private JButton miscolectivos;
	private JButton perfil;
	private JButton logOut;
	private JButton goBackButton;
	private JButton crearProyectoInfra;
	private JButton crearProyectoInfraFinal;
	private JButton crearColectivo;
	private JButton crearSubColectivo;
	private JButton crearColectivoFinal;
	private JButton crearSubColectivoFinal;
	private JButton crearProyectoSoc;
	private JButton crearProyectoSocFinal;
	private JButton imagen;
	private JButton apoyarProyecto;
	private JButton apoyarColectivos;
	private JButton suscribirseProyecto;
	private JButton solicitarFinanciacion;
	private JButton calcularPopularidad;
	private JButton calcularAfinidad;
	
	private JComboBox<String> combo;
		
	private JTable notificaciones;
	private DefaultTableModel defaultNotificaciones;

	String ruta = null;
	Colectivo colectivo = null;
	Proyecto auxProyect = null;

	/*
	 * Variable donde se gaudará el usuario admin que previamente habrá iniciado
	 * sesión
	 */
	private Usuario user;

	public JPanel Home(CardLayout cardlayout, Container contentPane)
			throws ClassNotFoundException, IOException, InvalidIDException {
		final Sistema sistema;
		sistema = Sistema.getInstancia();
		if ((user = sistema.usuarioLogin()) == null) {
			return null;
		}

		String[] columnNames = { "Notificacion", "Proyecto Afectado", "Tipo de Notificacion" };
		Object[][] data = new Object[][] {};

		defaultNotificaciones = new DefaultTableModel(data, columnNames);
		notificaciones = new JTable(defaultNotificaciones);

		for (Notificacion n : Sistema.getInstancia().usuarioLogin().getNotificaciones()) {
			Object[] newRow = { n.getTexto(), n.getProyectoNotif().getTitulo(), n.getTipo() };
			defaultNotificaciones.addRow(newRow);
		}

		/* Labels para el logo de la aplicación y el mensaje de bienvenida */
		JLabel picLabel = new JLabel(new ImageIcon(ImageIO.read(new File(".." + File.separator + "Tidea"
				+ File.separator + "src" + File.separator + "Application" + File.separator + "logo.jpeg"))));
		JLabel welcome = new JLabel("Bienvenido " + sistema.usuarioLogin().getNombre() + "!");
		welcome.setFont(new Font("Arial", Font.BOLD, 20));
		welcome.setHorizontalAlignment(SwingConstants.RIGHT);

		/* panel a devolver */
		JPanel jp = new JPanel();
		jp.setName("Tidea");
		jp.setLayout(new BorderLayout());
		jp.setBackground(new Color(236, 247, 231));

		/* panel para ajustar elementos a la izquierda */
		JPanel jpL = new JPanel();
		jpL.setLayout(new BoxLayout(jpL, BoxLayout.Y_AXIS));
		jpL.setBorder(new EmptyBorder(10, 10, 10, 10));
		jpL.setBackground(new Color(236, 247, 231));

		/* panel para ajustar elementos al centro */
		JPanel jpC = new JPanel();
		jpC.setLayout(new BoxLayout(jpC, BoxLayout.Y_AXIS));
		jpC.setBorder(new EmptyBorder(10, 10, 10, 10));
		jpC.setBackground(new Color(236, 247, 231));

		/* panel para ajustar elementos al centro */
		JPanel jpN = new JPanel();
		jpN.setLayout(new BoxLayout(jpN, BoxLayout.X_AXIS));
		jpN.setBorder(new EmptyBorder(10, 10, 10, 10));
		jpN.setBackground(new Color(236, 247, 231));

		/* creación y personalización de botones de este panel */
		home = new JButton("Home");
		home.setBackground(new Color(127, 232, 84));
		home.setMaximumSize(new Dimension(100, 35));
		home.setFont(new Font("Arial", Font.PLAIN, 16));
		home.setBorder(new LineBorder(Color.BLACK));

		proyectos = new JButton("Proyectos");
		proyectos.setBackground(new Color(150, 255, 150));
		proyectos.setMaximumSize(new Dimension(125, 35));
		proyectos.setFont(new Font("Arial", Font.PLAIN, 16));

		colectivos = new JButton("Colectivos");
		colectivos.setBackground(new Color(150, 255, 150));
		colectivos.setMaximumSize(new Dimension(125, 35));
		colectivos.setFont(new Font("Arial", Font.PLAIN, 16));

		logOut = new JButton("Cerrar Sesión");
		logOut.setBackground(new Color(150, 255, 150));
		logOut.setMaximumSize(new Dimension(150, 35));
		logOut.setFont(new Font("Arial", Font.BOLD, 16));

		misproyectos = new JButton("Mis Proyectos");
		misproyectos.setBackground(new Color(150, 255, 150));
		misproyectos.setMaximumSize(new Dimension(150, 70));
		misproyectos.setFont(new Font("Arial", Font.PLAIN, 18));

		miscolectivos = new JButton("Mis Colectivos");
		miscolectivos.setBackground(new Color(150, 255, 150));
		miscolectivos.setMaximumSize(new Dimension(150, 70));
		miscolectivos.setFont(new Font("Arial", Font.PLAIN, 18));

		perfil = new JButton("Perfil");
		perfil.setFont(new Font("Arial", Font.PLAIN, 18));
		perfil.setBackground(new Color(150, 255, 150));
		perfil.setMaximumSize(new Dimension(120, 70));

		/* añadir los botones en los paneles que queremos */

		jpL.add(welcome);
		jpL.add(Box.createRigidArea(new Dimension(15, 80)));
		jpL.add(home);
		jpL.add(Box.createRigidArea(new Dimension(15, 15)));
		jpL.add(proyectos);
		jpL.add(Box.createRigidArea(new Dimension(15, 15)));
		jpL.add(colectivos);
		jpL.add(Box.createRigidArea(new Dimension(15, 190)));
		jpL.add(logOut);

		jpN.add(picLabel);
		jpN.add(Box.createRigidArea(new Dimension(200, 0)));
		jpN.add(misproyectos);
		jpN.add(Box.createRigidArea(new Dimension(50, 0)));
		jpN.add(miscolectivos);
		jpN.add(Box.createRigidArea(new Dimension(300, 0)));
		jpN.add(perfil);

		/* NUEVO */
		notificaciones.setRowHeight(40);
		notificaciones.setAutoscrolls(true);
		notificaciones.setDefaultEditor(Object.class, null);
		notificaciones.setGridColor(Color.BLACK);
		
		JTableHeader header = notificaciones.getTableHeader();
		header.setBackground(new Color(50, 50, 50));
		header.setForeground(new Color(150, 255, 150));
		jpC.add(header);
		jpC.add(notificaciones);

		jp.add(jpC, BorderLayout.CENTER);
		jp.add(jpL, BorderLayout.WEST);
		jp.add(jpN, BorderLayout.NORTH);

		home.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Inicio");
			}
		});

		notificaciones.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				if (SwingUtilities.isRightMouseButton(e)) {
				} else if (e.getClickCount() == 2 && SwingUtilities.isLeftMouseButton(e)) {
					defaultNotificaciones.removeRow(notificaciones.getSelectedRow());
				}
			}
		});

		misproyectos.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Mis Proyectos");
			}
		});

		proyectos.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Proyectos");
			}
		});

		colectivos.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Colectivos");
			}
		});

		miscolectivos.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Mis Colectivos");
			}
		});

		perfil.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Perfil");
			}
		});

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
				catch (Exception e1) {
					e1.printStackTrace();
				}
			}
		});

		jp.setVisible(true);
		jp.setSize(300, 300);

		return jp;
	}

	public JPanel misProyectos(CardLayout cardlayout, Container contentPane)
			throws ClassNotFoundException, IOException, InvalidIDException {
		final Sistema sistema;
		sistema = Sistema.getInstancia();
		/* Labels para el logo de la aplicación y el mensaje de bienvenida */
		JLabel picLabel = new JLabel(new ImageIcon(ImageIO.read(new File(".." + File.separator + "Tidea"
				+ File.separator + "src" + File.separator + "Application" + File.separator + "logo.jpeg"))));
		JLabel welcome = new JLabel("Bienvenido " + sistema.usuarioLogin().getNombre() + "!");
		welcome.setFont(new Font("Arial", Font.BOLD, 20));
		welcome.setHorizontalAlignment(SwingConstants.RIGHT);

		/* panel a devolver */
		JPanel jp = new JPanel();
		jp.setName("Tidea");
		jp.setLayout(new BorderLayout());
		jp.setBackground(new Color(236, 247, 231));

		/* panel para ajustar elementos a la izquierda */
		JPanel jpL = new JPanel();
		jpL.setLayout(new BoxLayout(jpL, BoxLayout.Y_AXIS));
		jpL.setBorder(new EmptyBorder(10, 10, 10, 10));
		jpL.setBackground(new Color(236, 247, 231));

		/* panel para ajustar elementos al centro */
		JPanel jpC = new JPanel();
		jpC.setLayout(new BoxLayout(jpC, BoxLayout.Y_AXIS));
		jpC.setBorder(new EmptyBorder(10, 10, 10, 10));
		jpC.setBackground(new Color(236, 247, 231));

		/* panel para ajustar elementos al Norte */
		JPanel jpN = new JPanel();
		jpN.setLayout(new BoxLayout(jpN, BoxLayout.X_AXIS));
		jpN.setBorder(new EmptyBorder(10, 10, 10, 10));
		jpN.setBackground(new Color(236, 247, 231));

		/* Tablas mis proyectos */
		JLabel p1 = new JLabel("Proyectos creados por " + sistema.usuarioLogin().getNombre());
		p1.setFont(new Font("Arial", Font.BOLD, 18));
		p1.setHorizontalAlignment(SwingConstants.RIGHT);

		JLabel p2 = new JLabel("Proyectos a los que estas suscrito");
		p2.setFont(new Font("Arial", Font.BOLD, 18));
		p2.setHorizontalAlignment(SwingConstants.RIGHT);
		JTable tablaP1;
		JTable tablaP2;

		String[] columnNames = { "Proyecto", "Proponente", "Apoyos recibidos/necesarios" };
		Object[][] data = new Object[][] {};

		DefaultTableModel dataModel = new DefaultTableModel(data, columnNames);
		tablaP1 = new JTable(dataModel);
		tablaP2 = new JTable(dataModel);

		for (Proyecto p : user.getProyectosCreados()) {
			Object[] newRow = { p.getTitulo(), p.getUsuarioProponente().getNombre(),
					p.getApoyosRecibidos() + "/" + sistema.getApoyosFinanciacion() };
			dataModel.addRow(newRow);
		}

		for (Proyecto p : user.getProyectosSuscrito()) {
			Object[] newRow = { p.getTitulo(), p.getUsuarioProponente().getNombre(),
					p.getApoyosRecibidos() + "/" + sistema.getApoyosFinanciacion() };
			dataModel.addRow(newRow);
		}
		
		calcularPopularidad = new JButton("Calcular Popularidad");
		calcularPopularidad.setFont(new Font("Arial", Font.PLAIN, 18));
		calcularPopularidad.setBackground(new Color(50, 20, 150));
		calcularPopularidad.setMaximumSize(new Dimension(300, 50));
		calcularPopularidad.setForeground(Color.WHITE);

		JPanel jpD = new JPanel();
		jpD.setLayout(new BoxLayout(jpD, BoxLayout.Y_AXIS));
		jpD.setBackground(new Color(236, 247, 231));

		tablaP1.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				if (SwingUtilities.isRightMouseButton(e)) {
				} else if (e.getClickCount() == 2 && SwingUtilities.isLeftMouseButton(e)) {
					if (SwingUtilities.isRightMouseButton(e)) {
					} else if (e.getClickCount() == 2 && SwingUtilities.isLeftMouseButton(e)) {
						Proyecto proyecto = null;
						for (Proyecto p : sistema.getProyectos()) {
							if (p.getTitulo().equals(tablaP1.getValueAt(tablaP1.getSelectedRow(), 0).toString())) {
								proyecto = p;
							}
						}
						
						solicitarFinanciacion = new JButton("Solicitar Financiación");
						solicitarFinanciacion.setFont(new Font("Arial", Font.PLAIN, 14));
						solicitarFinanciacion.setBackground(new Color(50, 20, 150));
						solicitarFinanciacion.setMaximumSize(new Dimension(170, 35));
						solicitarFinanciacion.setForeground(Color.WHITE);
						
						JLabel detalleP = new JLabel("Información sobre el proyecto: " + proyecto.getTitulo());
						detalleP.setFont(new Font("Arial", Font.BOLD, 26));

						JLabel descripcion = new JLabel("Descripción: " + proyecto.getDescripcion());
						descripcion.setFont(new Font("Arial", Font.PLAIN, 16));

						JLabel estado = new JLabel("Estado del proyecto: " + proyecto.getEstadoProyecto());
						estado.setFont(new Font("Arial", Font.PLAIN, 16));

						JLabel apoyos = new JLabel("Numero de apoyos: " + proyecto.getApoyosRecibidos());
						apoyos.setFont(new Font("Arial", Font.PLAIN, 16));

						JLabel financiacion = new JLabel(
								"Estado de la financiación proyecto: " + proyecto.getEstadoFinanciacion());
						financiacion.setFont(new Font("Arial", Font.PLAIN, 16));
						try {
							goBackButton = new JButton(new ImageIcon(
									ImageIO.read(new File(".." + File.separator + "Tidea" + File.separator + "src"
											+ File.separator + "Application" + File.separator + "goback.png"))));
							goBackButton.setMaximumSize(new Dimension(65, 65));
						} catch (IOException e1) {
							e1.printStackTrace();
						}
						goBackButton.addActionListener(new ActionListener() {
							@Override
							public void actionPerformed(ActionEvent e) {
								jpD.removeAll();
								jpC.setVisible(true);
							}
						});
						auxProyect = proyecto;
						solicitarFinanciacion.addActionListener(new ActionListener() {
							@Override
							public void actionPerformed(ActionEvent e) {
								try {
									if (auxProyect.solicitarFinanciacion() != null) {
										JOptionPane.showMessageDialog(jp, "Financiación solicitada correctamente!");
										return;
									}
								} catch (IOException e1) {
									e1.printStackTrace();
								} catch (InvalidRequestException e1) {
									e1.printStackTrace();
								}
							}
						});

						jpC.setVisible(false);
						jpD.add(goBackButton, BorderLayout.WEST);
						jpD.add(Box.createRigidArea(new Dimension(15, 15)));
						jpD.add(detalleP);
						if (proyecto.getEstadoProyecto().equals(TipoEstadoProyecto.VOTOSALCANZADOS)) {
							jpD.add(Box.createRigidArea(new Dimension(15, 15)));
							jpD.add(solicitarFinanciacion);
						}
						jpD.add(Box.createRigidArea(new Dimension(30, 30)));
						jpD.add(descripcion);
						jpD.add(Box.createRigidArea(new Dimension(15, 15)));
						jpD.add(estado);
						jpD.add(Box.createRigidArea(new Dimension(15, 15)));
						jpD.add(financiacion);
						jpD.add(Box.createRigidArea(new Dimension(15, 15)));
						jpD.add(apoyos);
						if (proyecto.getProjectKind().equals(ProjectKind.Social)) {
							JLabel social = new JLabel("Descipcion grupo social: "
									+ ((ProyectoSocial) proyecto).getDescripcionGrupoSocial());
							social.setFont(new Font("Arial", Font.PLAIN, 16));
							jpD.add(Box.createRigidArea(new Dimension(15, 15)));
							jpD.add(social);
						}
						if (proyecto.getProjectKind().equals(ProjectKind.Infrastructure)) {
							JLabel distritos = new JLabel(
									"Distritos afectados: " + ((ProyectoInfraestructura) proyecto).getAfectados());
							distritos.setFont(new Font("Arial", Font.PLAIN, 16));
							jpD.add(Box.createRigidArea(new Dimension(15, 15)));
							jpD.add(distritos);
						}
						if (proyecto.getProjectKind().equals(ProjectKind.Infrastructure)) {
							JLabel picLabel;
							try {
								picLabel = new JLabel(new ImageIcon(
										ImageIO.read(new File(((ProyectoInfraestructura) proyecto).getImagen()))));
								jpD.add(Box.createRigidArea(new Dimension(15, 15)));
								jpD.add(picLabel);
							} catch (IOException e1) {
								e1.printStackTrace();
							}
						}
						jp.add(jpD, BorderLayout.CENTER);
					}
				}
			}
		});

		tablaP2.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				if (SwingUtilities.isRightMouseButton(e)) {
				} else if (e.getClickCount() == 2 && SwingUtilities.isLeftMouseButton(e)) {
					Proyecto proyecto = null;
					for (Proyecto p : sistema.getProyectos()) {
						if (p.getTitulo().equals(tablaP2.getValueAt(tablaP2.getSelectedRow(), 0).toString())) {
							proyecto = p;
						}
					}
					
					solicitarFinanciacion = new JButton("Solicitar Financiación");
					solicitarFinanciacion.setFont(new Font("Arial", Font.PLAIN, 14));
					solicitarFinanciacion.setBackground(new Color(50, 20, 150));
					solicitarFinanciacion.setMaximumSize(new Dimension(170, 35));
					solicitarFinanciacion.setForeground(Color.WHITE);
					
					JLabel detalleP = new JLabel("Información sobre el proyecto: " + proyecto.getTitulo());
					detalleP.setFont(new Font("Arial", Font.BOLD, 26));

					JLabel descripcion = new JLabel("Descripción: " + proyecto.getDescripcion());
					descripcion.setFont(new Font("Arial", Font.PLAIN, 16));

					JLabel estado = new JLabel("Estado del proyecto: " + proyecto.getEstadoProyecto());
					estado.setFont(new Font("Arial", Font.PLAIN, 16));

					JLabel apoyos = new JLabel("Numero de apoyos: " + proyecto.getApoyosRecibidos());
					apoyos.setFont(new Font("Arial", Font.PLAIN, 16));

					JLabel financiacion = new JLabel(
							"Estado de la financiación proyecto: " + proyecto.getEstadoFinanciacion());
					financiacion.setFont(new Font("Arial", Font.PLAIN, 16));
					try {
						goBackButton = new JButton(
								new ImageIcon(ImageIO.read(new File(".." + File.separator + "Tidea" + File.separator
										+ "src" + File.separator + "Application" + File.separator + "goback.png"))));
						goBackButton.setMaximumSize(new Dimension(65, 65));
					} catch (IOException e1) {
						e1.printStackTrace();
					}
					goBackButton.addActionListener(new ActionListener() {
						@Override
						public void actionPerformed(ActionEvent e) {
							jpD.removeAll();
							jpC.setVisible(true);
						}
					});
					
					solicitarFinanciacion.addActionListener(new ActionListener() {
						@Override
						public void actionPerformed(ActionEvent e) {
							try {
								if (auxProyect.solicitarFinanciacion() != null) {
									JOptionPane.showMessageDialog(jp, "Financiación solicitada correctamente!");
									return;
								}
							} catch (IOException e1) {
								e1.printStackTrace();
							} catch (InvalidRequestException e1) {
								e1.printStackTrace();
							}
						}
					});

					jpC.setVisible(false);
					jpD.add(goBackButton, BorderLayout.WEST);
					jpD.add(Box.createRigidArea(new Dimension(15, 15)));
					jpD.add(detalleP);
					
					if (proyecto.getEstadoProyecto().equals(TipoEstadoProyecto.VOTOSALCANZADOS)) {
						jpD.add(Box.createRigidArea(new Dimension(15, 15)));
						jpD.add(solicitarFinanciacion);
					}
					
					jpD.add(Box.createRigidArea(new Dimension(30, 30)));
					jpD.add(descripcion);
					jpD.add(Box.createRigidArea(new Dimension(15, 15)));
					jpD.add(estado);
					jpD.add(Box.createRigidArea(new Dimension(15, 15)));
					jpD.add(financiacion);
					jpD.add(Box.createRigidArea(new Dimension(15, 15)));
					jpD.add(apoyos);
					if (proyecto.getProjectKind().equals(ProjectKind.Social)) {
						JLabel social = new JLabel(
								"Descipcion grupo social: " + ((ProyectoSocial) proyecto).getDescripcionGrupoSocial());
						social.setFont(new Font("Arial", Font.PLAIN, 16));
						jpD.add(Box.createRigidArea(new Dimension(15, 15)));
						jpD.add(social);
					}
					if (proyecto.getProjectKind().equals(ProjectKind.Infrastructure)) {
						JLabel distritos = new JLabel(
								"Distritos afectados: " + ((ProyectoInfraestructura) proyecto).getAfectados());
						distritos.setFont(new Font("Arial", Font.PLAIN, 16));
						jpD.add(Box.createRigidArea(new Dimension(15, 15)));
						jpD.add(distritos);
					}
					if (proyecto.getProjectKind().equals(ProjectKind.Infrastructure)) {
						JLabel picLabel;
						try {
							picLabel = new JLabel(new ImageIcon(
									ImageIO.read(new File(((ProyectoInfraestructura) proyecto).getImagen()))));
							jpD.add(Box.createRigidArea(new Dimension(15, 15)));
							jpD.add(picLabel);
						} catch (IOException e1) {
							e1.printStackTrace();
						}
					}
					jp.add(jpD, BorderLayout.CENTER);
				}
			}

		});
		tablaP1.setRowHeight(30);
		tablaP1.setAutoscrolls(true);
		tablaP1.setDefaultEditor(Object.class, null);
		tablaP1.setGridColor(Color.BLACK);
		JTableHeader header = tablaP1.getTableHeader();
		header.setBackground(new Color(50, 50, 50));
		header.setForeground(new Color(150, 255, 150));
		tablaP2.setRowHeight(30);
		tablaP2.setAutoscrolls(true);
		tablaP2.setDefaultEditor(Object.class, null);
		tablaP2.setGridColor(Color.BLACK);
		JTableHeader header2 = tablaP2.getTableHeader();
		header2.setBackground(new Color(50, 50, 50));
		header2.setForeground(new Color(150, 255, 150));
		jpC.add(p1);
		jpC.add(header);
		jpC.add(tablaP1);
		jpC.add(Box.createRigidArea(new Dimension(30, 30)));
		jpC.add(p2);
		jpC.add(header2);
		jpC.add(tablaP2);
		jpC.add(Box.createRigidArea(new Dimension(40, 30)));
		jpC.add(calcularPopularidad);
		
		
		/* creación y personalización de botones de este panel */
		home = new JButton("Home");
		home.setBackground(new Color(150, 255, 150));
		home.setMaximumSize(new Dimension(100, 35));
		home.setFont(new Font("Arial", Font.PLAIN, 16));

		proyectos = new JButton("Proyectos");
		proyectos.setBackground(new Color(150, 255, 150));
		proyectos.setMaximumSize(new Dimension(125, 35));
		proyectos.setFont(new Font("Arial", Font.PLAIN, 16));
		proyectos.setBorder(new LineBorder(Color.BLACK));

		colectivos = new JButton("Colectivos");
		colectivos.setBackground(new Color(150, 255, 150));
		colectivos.setMaximumSize(new Dimension(125, 35));
		colectivos.setFont(new Font("Arial", Font.PLAIN, 16));

		logOut = new JButton("Cerrar Sesión");
		logOut.setBackground(new Color(150, 255, 150));
		logOut.setMaximumSize(new Dimension(150, 35));
		logOut.setFont(new Font("Arial", Font.BOLD, 16));

		misproyectos = new JButton("Mis Proyectos");
		misproyectos.setBackground(new Color(127, 232, 84));
		misproyectos.setMaximumSize(new Dimension(150, 70));
		misproyectos.setFont(new Font("Arial", Font.PLAIN, 18));

		miscolectivos = new JButton("Mis Colectivos");
		miscolectivos.setBackground(new Color(150, 255, 150));
		miscolectivos.setMaximumSize(new Dimension(150, 70));
		miscolectivos.setFont(new Font("Arial", Font.PLAIN, 18));

		perfil = new JButton("Perfil");
		perfil.setFont(new Font("Arial", Font.PLAIN, 18));
		perfil.setBackground(new Color(150, 255, 150));
		perfil.setMaximumSize(new Dimension(120, 70));

		/* añadir los botones en los paneles que queremos */

		jpL.add(welcome);
		jpL.add(Box.createRigidArea(new Dimension(15, 80)));
		jpL.add(home);
		jpL.add(Box.createRigidArea(new Dimension(15, 15)));
		jpL.add(proyectos);
		jpL.add(Box.createRigidArea(new Dimension(15, 15)));
		jpL.add(colectivos);
		jpL.add(Box.createRigidArea(new Dimension(15, 190)));
		jpL.add(logOut);

		jpN.add(picLabel);
		jpN.add(Box.createRigidArea(new Dimension(200, 0)));
		jpN.add(misproyectos);
		jpN.add(Box.createRigidArea(new Dimension(50, 0)));
		jpN.add(miscolectivos);
		jpN.add(Box.createRigidArea(new Dimension(300, 0)));
		jpN.add(perfil);

		jp.add(jpC, BorderLayout.CENTER);
		jp.add(jpL, BorderLayout.WEST);
		jp.add(jpN, BorderLayout.NORTH);

		home.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Inicio");
			}
		});

		misproyectos.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Mis Proyectos");
			}
		});
		
		calcularPopularidad.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				Proyecto proyecto = null;
				
				if (tablaP2.getSelectedRows().length == 1) {
					for (Proyecto p : sistema.getProyectos()) {
						if (p.getTitulo().equals(tablaP2.getValueAt(tablaP2.getSelectedRow(), 0).toString())) {
							proyecto = p;
						}
					}
					
					JOptionPane.showMessageDialog(jp, "Apoyos del proyecto: " + proyecto.getApoyosRecibidos());
					return;
		
				}
				
				else {
					JOptionPane.showMessageDialog(jp, "Tienes que seleccionar un proyecto de la tabla de susctritos");
					return;
				}
			}
		});

		proyectos.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Proyectos");
			}
		});

		colectivos.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Colectivos");
			}
		});

		miscolectivos.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Mis Colectivos");
			}
		});

		perfil.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Perfil");
			}
		});

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
				} catch (Exception e1) {
					e1.printStackTrace();
				}
			}
		});

		jp.setVisible(true);
		jp.setSize(300, 300);

		return jp;
	}

	public JPanel proyectos(CardLayout cardlayout, Container contentPane)
			throws ClassNotFoundException, IOException, InvalidIDException {
		final Sistema sistema;
		sistema = Sistema.getInstancia();
		/* Labels para el logo de la aplicación y el mensaje de bienvenida */
		JLabel picLabel = new JLabel(new ImageIcon(ImageIO.read(new File(".." + File.separator + "Tidea"
				+ File.separator + "src" + File.separator + "Application" + File.separator + "logo.jpeg"))));
		JLabel welcome = new JLabel("Bienvenido " + sistema.usuarioLogin().getNombre() + "!");
		welcome.setFont(new Font("Arial", Font.BOLD, 20));
		welcome.setHorizontalAlignment(SwingConstants.RIGHT);

		/* panel a devolver */
		JPanel jp = new JPanel();
		jp.setName("Tidea");
		jp.setLayout(new BorderLayout());
		jp.setBackground(new Color(236, 247, 231));

		/* panel para ajustar elementos a la izquierda */
		JPanel jpL = new JPanel();
		jpL.setLayout(new BoxLayout(jpL, BoxLayout.Y_AXIS));
		jpL.setBorder(new EmptyBorder(10, 10, 10, 10));
		jpL.setBackground(new Color(236, 247, 231));

		/* panel para ajustar elementos al centro */
		JPanel jpC = new JPanel();
		jpC.setLayout(new BoxLayout(jpC, BoxLayout.Y_AXIS));
		jpC.setBorder(new EmptyBorder(10, 10, 10, 10));
		jpC.setBackground(new Color(236, 247, 231));

		/* panel para ajustar elementos al centro */
		JPanel jpN = new JPanel();
		jpN.setLayout(new BoxLayout(jpN, BoxLayout.X_AXIS));
		jpN.setBorder(new EmptyBorder(10, 10, 10, 10));
		jpN.setBackground(new Color(236, 247, 231));

		/* Tabla proyectos */
		JTable tablaP;

		String[] columnNames = { "Proyecto", "Proponente", "Apoyos recibidos/necesarios" };
		Object[][] data = new Object[][] {};

		DefaultTableModel dataModel = new DefaultTableModel(data, columnNames);
		tablaP = new JTable(dataModel);

		for (Proyecto p : sistema.getProyectos()) {
			Object[] newRow = { p.getTitulo(), p.getUsuarioProponente().getNombre(),
					p.getApoyosRecibidos() + "/" + sistema.getApoyosFinanciacion() };
			dataModel.addRow(newRow);
		}
		
		JPanel jpMini = new JPanel();
		jpMini.setLayout(new BoxLayout(jpMini, BoxLayout.X_AXIS));
		jpMini.setBackground(new Color(236, 247, 231));
		
		apoyarProyecto = new JButton("Apoyar proyecto");
		apoyarProyecto.setFont(new Font("Arial", Font.PLAIN, 18));
		apoyarProyecto.setBackground(new Color(50, 20, 150));
		apoyarProyecto.setMaximumSize(new Dimension(300, 50));
		apoyarProyecto.setForeground(Color.WHITE);

		apoyarColectivos = new JButton("Apoyar como:");
		apoyarColectivos.setFont(new Font("Arial", Font.PLAIN, 18));
		apoyarColectivos.setBackground(new Color(50, 20, 150));
		apoyarColectivos.setMaximumSize(new Dimension(300, 50));
		apoyarColectivos.setForeground(Color.WHITE);
		
		suscribirseProyecto = new JButton("Suscribirse");
		suscribirseProyecto.setBackground(new Color(150, 255, 150));
		suscribirseProyecto.setMaximumSize(new Dimension(125, 35));
		suscribirseProyecto.setFont(new Font("Arial", Font.PLAIN, 16));
		
		JTextField textoColectivo = new JTextField(30);
		textoColectivo.setMaximumSize(new Dimension(400, 30));
		textoColectivo.setAlignmentX(Component.LEFT_ALIGNMENT);
		
		jpMini.add(textoColectivo);

		JPanel jpD = new JPanel();
		jpD.setLayout(new BoxLayout(jpD, BoxLayout.Y_AXIS));
		jpD.setBackground(new Color(236, 247, 231));

		tablaP.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				if (SwingUtilities.isRightMouseButton(e)) {
				} else if (e.getClickCount() == 2 && SwingUtilities.isLeftMouseButton(e)) {
					Proyecto proyecto = null;
					for (Proyecto p : sistema.getProyectos()) {
						if (p.getTitulo().equals(tablaP.getValueAt(tablaP.getSelectedRow(), 0).toString())) {
							proyecto = p;
						}
					}
					JLabel detalleP = new JLabel("Información sobre el proyecto: " + proyecto.getTitulo());
					detalleP.setFont(new Font("Arial", Font.BOLD, 26));

					JLabel descripcion = new JLabel("Descripción: " + proyecto.getDescripcion());
					descripcion.setFont(new Font("Arial", Font.PLAIN, 16));

					JLabel estado = new JLabel("Estado del proyecto: " + proyecto.getEstadoProyecto());
					estado.setFont(new Font("Arial", Font.PLAIN, 16));

					JLabel apoyos = new JLabel("Numero de apoyos: " + proyecto.getApoyosRecibidos());
					apoyos.setFont(new Font("Arial", Font.PLAIN, 16));

					JLabel financiacion = new JLabel(
							"Estado de la financiación proyecto: " + proyecto.getEstadoFinanciacion());
					financiacion.setFont(new Font("Arial", Font.PLAIN, 16));
					try {
						goBackButton = new JButton(
								new ImageIcon(ImageIO.read(new File(".." + File.separator + "Tidea" + File.separator
										+ "src" + File.separator + "Application" + File.separator + "goback.png"))));
						goBackButton.setMaximumSize(new Dimension(65, 65));
					} catch (IOException e1) {
						e1.printStackTrace();
					}
					goBackButton.addActionListener(new ActionListener() {
						@Override
						public void actionPerformed(ActionEvent e) {
							jpD.removeAll();
							jpC.setVisible(true);
						}
					});

					jpC.setVisible(false);
					jpD.add(goBackButton, BorderLayout.WEST);
					jpD.add(Box.createRigidArea(new Dimension(15, 15)));
					jpD.add(detalleP);
					jpD.add(Box.createRigidArea(new Dimension(30, 30)));
					jpD.add(descripcion);
					jpD.add(Box.createRigidArea(new Dimension(15, 15)));
					jpD.add(estado);
					jpD.add(Box.createRigidArea(new Dimension(15, 15)));
					jpD.add(financiacion);
					jpD.add(Box.createRigidArea(new Dimension(15, 15)));
					jpD.add(apoyos);
					if (proyecto.getProjectKind().equals(ProjectKind.Social)) {
						JLabel social = new JLabel(
								"Descipcion grupo social: " + ((ProyectoSocial) proyecto).getDescripcionGrupoSocial());
						social.setFont(new Font("Arial", Font.PLAIN, 16));
						jpD.add(Box.createRigidArea(new Dimension(15, 15)));
						jpD.add(social);
					}
					if (proyecto.getProjectKind().equals(ProjectKind.Infrastructure)) {
						JLabel distritos = new JLabel(
								"Distritos afectados: " + ((ProyectoInfraestructura) proyecto).getAfectados());
						distritos.setFont(new Font("Arial", Font.PLAIN, 16));
						jpD.add(Box.createRigidArea(new Dimension(15, 15)));
						jpD.add(distritos);
					}
					if (proyecto.getProjectKind().equals(ProjectKind.Infrastructure)) {
						JLabel picLabel;
						try {
							picLabel = new JLabel(new ImageIcon(
									ImageIO.read(new File(((ProyectoInfraestructura) proyecto).getImagen()))));
							jpD.add(Box.createRigidArea(new Dimension(15, 15)));
							jpD.add(picLabel);
						} catch (IOException e1) {
							e1.printStackTrace();
						}
					}
					jp.add(jpD, BorderLayout.CENTER);
				}
			}
		});
		jpC.setVisible(true);

		tablaP.setRowHeight(30);
		tablaP.setAutoscrolls(true);
		tablaP.setDefaultEditor(Object.class, null);
		tablaP.setGridColor(Color.BLACK);
		JScrollPane scrollPane = new JScrollPane(tablaP);
		JTableHeader header = tablaP.getTableHeader();
		header.setBackground(new Color(50, 50, 50));
		header.setForeground(new Color(150, 255, 150));
		jpC.add(header);

		jpC.add(scrollPane, BorderLayout.CENTER);
		jpC.add(Box.createRigidArea(new Dimension(150, 80)));
		jpC.add(suscribirseProyecto);
		jpC.add(Box.createRigidArea(new Dimension(10, 10)));
		jpC.add(apoyarProyecto);
		jpC.add(Box.createRigidArea(new Dimension(20, 20)));
		jpC.add(apoyarColectivos);
		jpC.add(Box.createRigidArea(new Dimension(10, 10)));
		jpC.add(textoColectivo);

		/* creación y personalización de botones de este panel */
		home = new JButton("Home");
		home.setBackground(new Color(150, 255, 150));
		home.setMaximumSize(new Dimension(100, 35));
		home.setFont(new Font("Arial", Font.PLAIN, 16));

		proyectos = new JButton("Proyectos");
		proyectos.setBackground(new Color(127, 232, 84));
		proyectos.setMaximumSize(new Dimension(125, 35));
		proyectos.setFont(new Font("Arial", Font.PLAIN, 16));
		proyectos.setBorder(new LineBorder(Color.BLACK));

		colectivos = new JButton("Colectivos");
		colectivos.setBackground(new Color(150, 255, 150));
		colectivos.setMaximumSize(new Dimension(125, 35));
		colectivos.setFont(new Font("Arial", Font.PLAIN, 16));

		logOut = new JButton("Cerrar Sesión");
		logOut.setBackground(new Color(150, 255, 150));
		logOut.setMaximumSize(new Dimension(150, 35));
		logOut.setFont(new Font("Arial", Font.BOLD, 16));

		misproyectos = new JButton("Mis Proyectos");
		misproyectos.setBackground(new Color(150, 255, 150));
		misproyectos.setMaximumSize(new Dimension(150, 70));
		misproyectos.setFont(new Font("Arial", Font.PLAIN, 18));

		miscolectivos = new JButton("Mis Colectivos");
		miscolectivos.setBackground(new Color(150, 255, 150));
		miscolectivos.setMaximumSize(new Dimension(150, 70));
		miscolectivos.setFont(new Font("Arial", Font.PLAIN, 18));

		perfil = new JButton("Perfil");
		perfil.setFont(new Font("Arial", Font.PLAIN, 18));
		perfil.setBackground(new Color(150, 255, 150));
		perfil.setMaximumSize(new Dimension(120, 70));

		/* añadir los botones en los paneles que queremos */

		jpL.add(welcome);
		jpL.add(Box.createRigidArea(new Dimension(15, 80)));
		jpL.add(home);
		jpL.add(Box.createRigidArea(new Dimension(15, 15)));
		jpL.add(proyectos);
		jpL.add(Box.createRigidArea(new Dimension(15, 15)));
		jpL.add(colectivos);
		jpL.add(Box.createRigidArea(new Dimension(15, 190)));
		jpL.add(logOut);

		jpN.add(picLabel);
		jpN.add(Box.createRigidArea(new Dimension(200, 0)));
		jpN.add(misproyectos);
		jpN.add(Box.createRigidArea(new Dimension(50, 0)));
		jpN.add(miscolectivos);
		jpN.add(Box.createRigidArea(new Dimension(300, 0)));
		jpN.add(perfil);

		jp.add(jpC, BorderLayout.CENTER);
		jp.add(jpL, BorderLayout.WEST);
		jp.add(jpN, BorderLayout.NORTH);

		home.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Inicio");
			}
		});

		misproyectos.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Mis Proyectos");
			}
		});

		proyectos.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Proyectos");
			}
		});

		apoyarProyecto.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				Proyecto proyecto = null;
				
				if (tablaP.getSelectedRows().length == 1) {
					for (Proyecto p : sistema.getProyectos()) {
						if (p.getTitulo().equals(tablaP.getValueAt(tablaP.getSelectedRow(), 0).toString())) {
							proyecto = p;
						}
					}
					
					try {
						if (proyecto.apoyarProyecto() == false) {
							JOptionPane.showMessageDialog(jp, "Ya estás apoyando al proyecto!!", "Error",
									JOptionPane.ERROR_MESSAGE);
							return;
						}
						
						else {
							JOptionPane.showMessageDialog(jp, "Proyecto apoyado correctamente");
							return;
						}
						
						
					} catch (ClassNotFoundException | IOException | InvalidIDException e1) {
						e1.printStackTrace();
					}
				}
				
				else {
					JOptionPane.showMessageDialog(jp, "Debes seleccionar un proyecto");
					return;
				}
				
			}
		});

		apoyarColectivos.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				Proyecto proyecto = null;
				
				if (tablaP.getSelectedRows().length == 1) {
					for (Proyecto p : sistema.getProyectos()) {
						if (p.getTitulo().equals(tablaP.getValueAt(tablaP.getSelectedRow(), 0).toString())) {
							proyecto = p;
						}
					}

					Colectivo colectivo = null;
					for (Colectivo c : sistema.getColectivos()) {
						if (c.getNombre().equals(textoColectivo.getText())) {
							colectivo = c;
						}
					}

					try {
						if (proyecto.apoyarProyectoRepresentante(colectivo) == false) {
							JOptionPane.showMessageDialog(jp, "Ya estás apoyando al proyecto!!", "Error",
									JOptionPane.ERROR_MESSAGE);
							return;
						}
						
						else {
							JOptionPane.showMessageDialog(jp, "Proyecto apoyado correctamente");
							return;
						}
						
					} catch (ClassNotFoundException | IOException | InvalidIDException e1) {
						e1.printStackTrace();
					}
				}
				
				else {
					JOptionPane.showMessageDialog(jp, "Debes seleccionar un proyecto");
					return;
				}
			
			}
		});
		
		suscribirseProyecto.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				Proyecto proyecto = null;
				
				if (tablaP.getSelectedRows().length == 1) {
					for (Proyecto p : sistema.getProyectos()) {
						if (p.getTitulo().equals(tablaP.getValueAt(tablaP.getSelectedRow(), 0).toString())) {
							proyecto = p;
						}
			
					}
					
					try {
						if (proyecto.suscriberseProyecto() == true) {
							JOptionPane.showMessageDialog(jp, "Te has suscrito al proyecto "+ proyecto.getTitulo());
							return;
						}
						
						else {
							JOptionPane.showMessageDialog(jp, "Ya estas suscrito al proyecto "+ proyecto.getTitulo());
							return;
						}
					} catch (HeadlessException | ClassNotFoundException | IOException | InvalidIDException e1) {
						e1.printStackTrace();
					}
				}
				
				else {
					JOptionPane.showMessageDialog(jp, "Debes seleccionar un proyecto");
					return;
				}
				
			
			}
		});

		colectivos.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Colectivos");
			}
		});

		miscolectivos.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Mis Colectivos");
			}
		});

		perfil.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Perfil");
			}
		});

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
				} catch (Exception e1) {
					e1.printStackTrace();
				}
			}
		});

		jp.setVisible(true);
		jp.setSize(300, 300);

		return jp;
	}

	public JPanel colectivos(CardLayout cardlayout, Container contentPane)
			throws ClassNotFoundException, IOException, InvalidIDException {
		final Sistema sistema;
		sistema = Sistema.getInstancia();
		/* Labels para el logo de la aplicación y el mensaje de bienvenida */
		JLabel picLabel = new JLabel(new ImageIcon(ImageIO.read(new File(".." + File.separator + "Tidea"
				+ File.separator + "src" + File.separator + "Application" + File.separator + "logo.jpeg"))));
		JLabel welcome = new JLabel("Bienvenido " + sistema.usuarioLogin().getNombre() + "!");
		welcome.setFont(new Font("Arial", Font.BOLD, 20));
		welcome.setHorizontalAlignment(SwingConstants.RIGHT);

		/* panel a devolver */
		JPanel jp = new JPanel();
		jp.setName("Tidea");
		jp.setLayout(new BorderLayout());
		jp.setBackground(new Color(236, 247, 231));

		/* panel para ajustar elementos a la izquierda */
		JPanel jpL = new JPanel();
		jpL.setLayout(new BoxLayout(jpL, BoxLayout.Y_AXIS));
		jpL.setBorder(new EmptyBorder(10, 10, 10, 10));
		jpL.setBackground(new Color(236, 247, 231));

		/* panel para ajustar elementos al centro */
		JPanel jpC = new JPanel();
		jpC.setLayout(new BoxLayout(jpC, BoxLayout.Y_AXIS));
		jpC.setBorder(new EmptyBorder(10, 10, 10, 10));
		jpC.setBackground(new Color(236, 247, 231));

		/* panel para ajustar elementos al centro */
		JPanel jpN = new JPanel();
		jpN.setLayout(new BoxLayout(jpN, BoxLayout.X_AXIS));
		jpN.setBorder(new EmptyBorder(10, 10, 10, 10));
		jpN.setBackground(new Color(236, 247, 231));

		/* Tabla proyectos */
		JTable tablaP;

		String[] columnNames = { "Colectivo", "Representante", "Número de miembros" };
		Object[][] data = new Object[][] {};

		DefaultTableModel dataModel = new DefaultTableModel(data, columnNames);
		tablaP = new JTable(dataModel);

		for (Colectivo c : sistema.getColectivos()) {
			Object[] newRow = { c.getNombre(), c.getRepresentante().getNombre(), c.getIntegrantesColectivo().size() };
			dataModel.addRow(newRow);
		}

		JButton unirseColectivo = new JButton("Unirse a coletivo");
		unirseColectivo.setBackground(new Color(150, 255, 150));
		unirseColectivo.setMaximumSize(new Dimension(200, 40));
		unirseColectivo.setFont(new Font("Arial", Font.PLAIN, 20));

		JPanel jpD = new JPanel();
		jpD.setLayout(new BoxLayout(jpD, BoxLayout.Y_AXIS));
		jpD.setBackground(new Color(236, 247, 231));

		tablaP.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				if (SwingUtilities.isRightMouseButton(e)) {
				} else if (e.getClickCount() == 2 && SwingUtilities.isLeftMouseButton(e)) {
					Colectivo colectivo = null;
					for (Colectivo c : sistema.getColectivos()) {
						if (c.getNombre().equals(tablaP.getValueAt(tablaP.getSelectedRow(), 0).toString())) {
							colectivo = c;
						}
					}
					JLabel detalleC = new JLabel("Información sobre el colectivo: " + colectivo.getNombre());
					detalleC.setFont(new Font("Arial", Font.BOLD, 26));

					JLabel representante = new JLabel(
							"Representante del colectivo: " + colectivo.getRepresentante().getNombre());
					representante.setFont(new Font("Arial", Font.PLAIN, 16));

					String nombres = "";

					for (Usuario u : colectivo.getIntegrantesColectivo()) {
						nombres += u.getNombre() + ", ";
					}

					JLabel integrantes = new JLabel("Integrantes del colectivo: " + nombres);
					integrantes.setFont(new Font("Arial", Font.PLAIN, 16));

					String subcolectivos = "";

					for (Colectivo c : colectivo.getSubcolectivos()) {
						subcolectivos += c.getNombre() + ", ";
					}

					JLabel subC = new JLabel("Subcolectivos del colectivo: " + subcolectivos);
					subC.setFont(new Font("Arial", Font.PLAIN, 16));

					try {
						goBackButton = new JButton(
								new ImageIcon(ImageIO.read(new File(".." + File.separator + "Tidea" + File.separator
										+ "src" + File.separator + "Application" + File.separator + "goback.png"))));
						goBackButton.setMaximumSize(new Dimension(65, 65));
					} catch (IOException e1) {
						e1.printStackTrace();
					}
					goBackButton.addActionListener(new ActionListener() {
						@Override
						public void actionPerformed(ActionEvent e) {
							jpD.removeAll();
							jpC.setVisible(true);
						}
					});

					jpC.setVisible(false);
					jpD.add(goBackButton, BorderLayout.WEST);
					jpD.add(Box.createRigidArea(new Dimension(15, 15)));
					jpD.add(detalleC);
					jpD.add(Box.createRigidArea(new Dimension(30, 30)));
					jpD.add(representante);
					jpD.add(Box.createRigidArea(new Dimension(15, 15)));
					jpD.add(integrantes);
					jpD.add(Box.createRigidArea(new Dimension(15, 15)));
					jpD.add(subC);
					jp.add(jpD, BorderLayout.CENTER);
				}
			}
		});
		tablaP.setRowHeight(30);
		tablaP.setAutoscrolls(true);
		tablaP.setDefaultEditor(Object.class, null);
		tablaP.setGridColor(Color.BLACK);
		JScrollPane scrollPane = new JScrollPane(tablaP);
		JTableHeader header = tablaP.getTableHeader();
		header.setBackground(new Color(50, 50, 50));
		header.setForeground(new Color(150, 255, 150));
		jpC.add(header);
		jpC.add(scrollPane);
		jpC.add(Box.createRigidArea(new Dimension(200, 100)));
		jpC.add(unirseColectivo);

		/* creación y personalización de botones de este panel */
		home = new JButton("Home");
		home.setBackground(new Color(150, 255, 150));
		home.setMaximumSize(new Dimension(100, 35));
		home.setFont(new Font("Arial", Font.PLAIN, 16));

		proyectos = new JButton("Proyectos");
		proyectos.setBackground(new Color(150, 255, 150));
		proyectos.setMaximumSize(new Dimension(125, 35));
		proyectos.setFont(new Font("Arial", Font.PLAIN, 16));

		colectivos = new JButton("Colectivos");
		colectivos.setBackground(new Color(127, 232, 84));
		colectivos.setMaximumSize(new Dimension(125, 35));
		colectivos.setFont(new Font("Arial", Font.PLAIN, 16));
		colectivos.setBorder(new LineBorder(Color.BLACK));

		logOut = new JButton("Cerrar Sesión");
		logOut.setBackground(new Color(150, 255, 150));
		logOut.setMaximumSize(new Dimension(150, 35));
		logOut.setFont(new Font("Arial", Font.BOLD, 16));

		misproyectos = new JButton("Mis Proyectos");
		misproyectos.setBackground(new Color(150, 255, 150));
		misproyectos.setMaximumSize(new Dimension(150, 70));
		misproyectos.setFont(new Font("Arial", Font.PLAIN, 18));

		miscolectivos = new JButton("Mis Colectivos");
		miscolectivos.setBackground(new Color(150, 255, 150));
		miscolectivos.setMaximumSize(new Dimension(150, 70));
		miscolectivos.setFont(new Font("Arial", Font.PLAIN, 18));

		perfil = new JButton("Perfil");
		perfil.setFont(new Font("Arial", Font.PLAIN, 18));
		perfil.setBackground(new Color(150, 255, 150));
		perfil.setMaximumSize(new Dimension(120, 70));

		/* añadir los botones en los paneles que queremos */

		jpL.add(welcome);
		jpL.add(Box.createRigidArea(new Dimension(15, 80)));
		jpL.add(home);
		jpL.add(Box.createRigidArea(new Dimension(15, 15)));
		jpL.add(proyectos);
		jpL.add(Box.createRigidArea(new Dimension(15, 15)));
		jpL.add(colectivos);
		jpL.add(Box.createRigidArea(new Dimension(15, 190)));
		jpL.add(logOut);

		jpN.add(picLabel);
		jpN.add(Box.createRigidArea(new Dimension(200, 0)));
		jpN.add(misproyectos);
		jpN.add(Box.createRigidArea(new Dimension(50, 0)));
		jpN.add(miscolectivos);
		jpN.add(Box.createRigidArea(new Dimension(300, 0)));
		jpN.add(perfil);

		jp.add(jpC, BorderLayout.CENTER);
		jp.add(jpL, BorderLayout.WEST);
		jp.add(jpN, BorderLayout.NORTH);

		home.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Inicio");
			}
		});

		misproyectos.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Mis Proyectos");
			}
		});

		proyectos.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Proyectos");
			}
		});

		colectivos.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Colectivos");
			}
		});

		unirseColectivo.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				Colectivo colectivo = null;
				if (tablaP.getSelectedRows().length ==1) {
					for (Colectivo c : sistema.getColectivos()) {
						if (c.getNombre().equals(tablaP.getValueAt(tablaP.getSelectedRow(), 0).toString())) {
							colectivo = c;
						}
					}
					try {
						if (colectivo.unirseColectivo() == false) {
							JOptionPane.showMessageDialog(contentPane, "No es posible unirse a este colectivo");
							return;
						}
						
						else {
							JOptionPane.showMessageDialog(contentPane, "Te has unido correctamente a " + colectivo.getNombre());
							return;
						}
					} catch (ClassNotFoundException | IOException | InvalidIDException e1) {
						e1.printStackTrace();
					}
				}
				
				else {
					JOptionPane.showMessageDialog(contentPane, "Debes seleccionar un colectivo");
					return;
				}
				
			}
		});

		miscolectivos.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Mis Colectivos");
			}
		});

		perfil.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Perfil");
			}
		});

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
				} catch (Exception e1) {
					e1.printStackTrace();
				}
			}
		});

		jp.setVisible(true);
		jp.setSize(300, 300);

		return jp;
	}

	public JPanel misColectivos(CardLayout cardlayout, Container contentPane)
			throws IOException, ClassNotFoundException, InvalidIDException {
		final Sistema sistema;
		sistema = Sistema.getInstancia();
		if ((user = sistema.usuarioLogin()) == null) {
			user = sistema.logIn("JuanMoreno", "usuario1");
		}

		/* Labels para el logo de la aplicación y el mensaje de bienvenida */
		JLabel picLabel = new JLabel(new ImageIcon(ImageIO.read(new File(".." + File.separator + "Tidea"
				+ File.separator + "src" + File.separator + "Application" + File.separator + "logo.jpeg"))));
		JLabel welcome = new JLabel("Bienvenido " + sistema.usuarioLogin().getNombre() + "!");
		welcome.setFont(new Font("Arial", Font.BOLD, 20));
		welcome.setHorizontalAlignment(SwingConstants.RIGHT);

		/* panel a devolver */
		JPanel jp = new JPanel();
		jp.setName("Tidea");
		jp.setLayout(new BorderLayout());
		jp.setBackground(new Color(236, 247, 231));

		/* panel para ajustar elementos a la izquierda */
		JPanel jpL = new JPanel();
		jpL.setLayout(new BoxLayout(jpL, BoxLayout.Y_AXIS));
		jpL.setBorder(new EmptyBorder(10, 10, 10, 10));
		jpL.setBackground(new Color(236, 247, 231));

		/* panel para ajustar elementos al centro */
		JPanel jpC = new JPanel();
		jpC.setLayout(new BoxLayout(jpC, BoxLayout.Y_AXIS));
		jpC.setBorder(new EmptyBorder(10, 10, 10, 10));
		jpC.setBackground(new Color(236, 247, 231));

		/* panel para ajustar elementos al centro */
		JPanel jpN = new JPanel();
		jpN.setLayout(new BoxLayout(jpN, BoxLayout.X_AXIS));
		jpN.setBorder(new EmptyBorder(10, 10, 10, 10));
		jpN.setBackground(new Color(236, 247, 231));

		JButton dejarColectivo = new JButton("Dejar Colectivo");
		dejarColectivo.setBackground(new Color(150, 255, 150));
		dejarColectivo.setMaximumSize(new Dimension(200, 40));
		dejarColectivo.setFont(new Font("Arial", Font.PLAIN, 20));

		JTable tablaP;

		String[] columnNames = { "Colectivo", "Representante", "Número de miembros" };
		Object[][] data = new Object[][] {};

		DefaultTableModel dataModel = new DefaultTableModel(data, columnNames);
		tablaP = new JTable(dataModel);

		for (Colectivo c : user.getColectivosdeUsuario()) {
			Object[] newRow = { c.getNombre(), c.getRepresentante().getNombre(), c.getIntegrantesColectivo().size() };
			dataModel.addRow(newRow);
		}
		
		calcularAfinidad = new JButton("Calcular Afinidad");
		calcularAfinidad.setFont(new Font("Arial", Font.PLAIN, 20));
		calcularAfinidad.setBackground(new Color(50, 20, 150));
		calcularAfinidad.setMaximumSize(new Dimension(300, 50));
		calcularAfinidad.setMaximumSize(new Dimension(200, 40));
		calcularAfinidad.setForeground(Color.WHITE);
		
		JPanel jpD = new JPanel();
		jpD.setLayout(new BoxLayout(jpD, BoxLayout.Y_AXIS));
		jpD.setBackground(new Color(236, 247, 231));

		tablaP.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				if (SwingUtilities.isRightMouseButton(e)) {
				} else if (e.getClickCount() == 2 && SwingUtilities.isLeftMouseButton(e)) {
					
					for (Colectivo c : sistema.getColectivos()) {
						if (c.getNombre().equals(tablaP.getValueAt(tablaP.getSelectedRow(), 0).toString())) {
							colectivo = c;
						}
					}
					JLabel detalleC = new JLabel("Información sobre el colectivo: " + colectivo.getNombre());
					detalleC.setFont(new Font("Arial", Font.BOLD, 26));

					JLabel representante = new JLabel(
							"Representante del colectivo: " + colectivo.getRepresentante().getNombre());
					representante.setFont(new Font("Arial", Font.PLAIN, 16));

					String nombres = "";

					for (Usuario u : colectivo.getIntegrantesColectivo()) {
						nombres += u.getNombre() + ", ";
					}

					JLabel integrantes = new JLabel("Integrantes del colectivo: " + nombres);
					integrantes.setFont(new Font("Arial", Font.PLAIN, 16));

					String subcolectivos = "";

					for (Colectivo c : colectivo.getSubcolectivos()) {
						subcolectivos += c.getNombre() + ", ";
					}

					JLabel subC = new JLabel("Subcolectivos del colectivo: " + subcolectivos);
					subC.setFont(new Font("Arial", Font.PLAIN, 16));

					try {
						goBackButton = new JButton(
								new ImageIcon(ImageIO.read(new File(".." + File.separator + "Tidea" + File.separator
										+ "src" + File.separator + "Application" + File.separator + "goback.png"))));
						goBackButton.setMaximumSize(new Dimension(65, 65));
					} catch (IOException e1) {
						e1.printStackTrace();
					}
					
					crearSubColectivo = new JButton("Crear Subcolectivo");
					crearSubColectivo.setFont(new Font("Arial", Font.PLAIN, 14));
					crearSubColectivo.setBackground(new Color(230, 20, 20));
					crearSubColectivo.setMaximumSize(new Dimension(200, 35));
					crearSubColectivo.setForeground(Color.WHITE);
					
					
					JPanel jpE = new JPanel();
					jpE.setLayout(new BoxLayout(jpE, BoxLayout.Y_AXIS));
					jpE.setBackground(new Color(236, 247, 231));
					
					
					crearSubColectivo.addActionListener(new ActionListener() {
						@Override
						public void actionPerformed(ActionEvent e) {
							/* Label for NIF in LogIn */
							JLabel nombreColLabel = new JLabel("Nombre del Colectivo", JLabel.TRAILING);

							JTextField nombreColText = new JTextField(10);
							nombreColLabel.setLabelFor(nombreColText);
							nombreColText.setMaximumSize(new Dimension(400, 30));
							nombreColText.setAlignmentX(Component.LEFT_ALIGNMENT);							

							try {
								goBackButton = new JButton(
										new ImageIcon(ImageIO.read(new File(".." + File.separator + "Tidea" + File.separator + "src"
												+ File.separator + "Application" + File.separator + "goback.png"))));
								goBackButton.setMaximumSize(new Dimension(65, 65));
							} catch (IOException e1) {
								e1.printStackTrace();
							}
							goBackButton.addActionListener(new ActionListener() {
								@Override
								public void actionPerformed(ActionEvent e) {
									jpE.removeAll();
									jpD.setVisible(true);
								}
							});

							crearSubColectivoFinal = new JButton("Crear Subolectivo");
							crearSubColectivoFinal.setFont(new Font("Arial", Font.PLAIN, 14));
							crearSubColectivoFinal.setBackground(new Color(230, 20, 20));
							crearSubColectivoFinal.setMaximumSize(new Dimension(200, 35));
							crearSubColectivoFinal.setForeground(Color.WHITE);

							crearSubColectivoFinal.addActionListener(new ActionListener() {
								@Override
								public void actionPerformed(ActionEvent e) {
									if (nombreColText.getText().equals("")) {
										JOptionPane.showMessageDialog(contentPane, "Campo Obligatorio sin rellenar!");
										return;
									} else {
										try {
											if (colectivo.crearSubColectivo(nombreColText.getText()) != null) {
												JOptionPane.showMessageDialog(contentPane, "Subcolectivo creado correctamente!");
												return;
											}
											
										} catch (ClassNotFoundException | IOException | InvalidIDException e1) {
											e1.printStackTrace();
										}
									}
								}
							});

							jpD.setVisible(false);

							jpE.add(nombreColLabel);
							jpE.add(nombreColText);

							jpE.add(Box.createRigidArea(new Dimension(15, 100)));
							jpE.add(crearSubColectivoFinal, BorderLayout.WEST);
							jpE.add(Box.createRigidArea(new Dimension(15, 15)));
							jpE.add(goBackButton, BorderLayout.WEST);

							jp.add(jpE, BorderLayout.CENTER);
						}
					});
					
					
					
					goBackButton.addActionListener(new ActionListener() {
						@Override
						public void actionPerformed(ActionEvent e) {
							jpD.removeAll();
							jpC.setVisible(true);
						}
					});

					jpC.setVisible(false);
					jpD.add(goBackButton, BorderLayout.WEST);
					jpD.add(Box.createRigidArea(new Dimension(15, 15)));
					jpD.add(detalleC);
					jpD.add(Box.createRigidArea(new Dimension(30, 30)));
					jpD.add(representante);
					jpD.add(Box.createRigidArea(new Dimension(15, 15)));
					jpD.add(integrantes);
					jpD.add(Box.createRigidArea(new Dimension(15, 15)));
					jpD.add(subC);
					jpD.add(Box.createRigidArea(new Dimension(15, 80)));
					jpD.add(crearSubColectivo);
					jp.add(jpD, BorderLayout.CENTER);
				}
			}
		});
		tablaP.setRowSelectionAllowed(true);
		tablaP.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);
		tablaP.setRowHeight(30);
		tablaP.setAutoscrolls(true);
		tablaP.setDefaultEditor(Object.class, null);
		tablaP.setGridColor(Color.BLACK);
		JTableHeader header = tablaP.getTableHeader();
		header.setBackground(new Color(50, 50, 50));
		header.setForeground(new Color(150, 255, 150));
		jpC.add(header);
		jpC.add(tablaP);
		jpC.add(Box.createRigidArea(new Dimension(200, 200)));
		jpC.add(dejarColectivo);
		jpC.add(Box.createRigidArea(new Dimension(15, 15)));
		jpC.add(calcularAfinidad);

		/* creación y personalización de botones de este panel */
		home = new JButton("Home");
		home.setBackground(new Color(150, 255, 150));
		home.setMaximumSize(new Dimension(100, 35));
		home.setFont(new Font("Arial", Font.PLAIN, 16));
		home.setBorder(new LineBorder(Color.BLACK));

		proyectos = new JButton("Proyectos");
		proyectos.setBackground(new Color(150, 255, 150));
		proyectos.setMaximumSize(new Dimension(125, 35));
		proyectos.setFont(new Font("Arial", Font.PLAIN, 16));

		colectivos = new JButton("Colectivos");
		colectivos.setBackground(new Color(150, 255, 150));
		colectivos.setMaximumSize(new Dimension(125, 35));
		colectivos.setFont(new Font("Arial", Font.PLAIN, 16));

		logOut = new JButton("Cerrar Sesión");
		logOut.setBackground(new Color(150, 255, 150));
		logOut.setMaximumSize(new Dimension(150, 35));
		logOut.setFont(new Font("Arial", Font.BOLD, 16));

		misproyectos = new JButton("Mis Proyectos");
		misproyectos.setBackground(new Color(150, 255, 150));
		misproyectos.setMaximumSize(new Dimension(150, 70));
		misproyectos.setFont(new Font("Arial", Font.PLAIN, 18));

		miscolectivos = new JButton("Mis Colectivos");
		miscolectivos.setBackground(new Color(127, 232, 84));
		miscolectivos.setMaximumSize(new Dimension(150, 70));
		miscolectivos.setFont(new Font("Arial", Font.PLAIN, 18));

		perfil = new JButton("Perfil");
		perfil.setFont(new Font("Arial", Font.PLAIN, 18));
		perfil.setBackground(new Color(150, 255, 150));
		perfil.setMaximumSize(new Dimension(120, 70));

		/* añadir los botones en los paneles que queremos */

		jpL.add(welcome);
		jpL.add(Box.createRigidArea(new Dimension(15, 80)));
		jpL.add(home);
		jpL.add(Box.createRigidArea(new Dimension(15, 15)));
		jpL.add(proyectos);
		jpL.add(Box.createRigidArea(new Dimension(15, 15)));
		jpL.add(colectivos);
		jpL.add(Box.createRigidArea(new Dimension(15, 190)));
		jpL.add(logOut);

		jpN.add(picLabel);
		jpN.add(Box.createRigidArea(new Dimension(200, 0)));
		jpN.add(misproyectos);
		jpN.add(Box.createRigidArea(new Dimension(50, 0)));
		jpN.add(miscolectivos);
		jpN.add(Box.createRigidArea(new Dimension(300, 0)));
		jpN.add(perfil);

		jp.add(jpC, BorderLayout.CENTER);
		jp.add(jpL, BorderLayout.WEST);
		jp.add(jpN, BorderLayout.NORTH);

		home.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Inicio");
			}
		});

		misproyectos.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Mis Proyectos");
			}
		});

		proyectos.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Proyectos");
			}
		});

		colectivos.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Colectivos");
			}
		});

		miscolectivos.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Mis Colectivos");
			}
		});
		
		calcularAfinidad.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				Colectivo colectivo1 = null;
				Colectivo colectivo2 = null;
				Double res = null;
				
				if (tablaP.getSelectedRows().length == 2) {
					for (Colectivo c : sistema.getColectivos()) {
						if (c.getNombre().equals(tablaP.getValueAt(tablaP.getSelectedRow(), 0).toString())) {
							colectivo1 = c;
						}
					}
					
					for (Colectivo c : sistema.getColectivos()) {
						if (c.getNombre().equals(tablaP.getValueAt(tablaP.getSelectedRow(), 0).toString())) {
							colectivo2 = c;
						}
					}
					
				}
				
				else {
					JOptionPane.showMessageDialog(contentPane, "Debes seleccionar dos colectivos");
					return;
				}
				
				try {
					res =  colectivo1.afinidadColectivos(colectivo2);
				} catch (ClassNotFoundException | IOException | InvalidIDException e1) {
					e1.printStackTrace();
				}
				
				if (res != null) {
					JOptionPane.showMessageDialog(contentPane, "Afinidad entre los colectivos: " + res);
					return;
				}
				
				
			}
		});

		dejarColectivo.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				Colectivo colectivo = null;
				
				if (tablaP.getSelectedRows().length == 1) {
					for (Colectivo c : sistema.getColectivos()) {
						if (c.getNombre().equals(tablaP.getValueAt(tablaP.getSelectedRow(), 0).toString())) {
							colectivo = c;
						}
					}
					try {
						colectivo.abandonarColectivo();
						dataModel.removeRow(tablaP.getSelectedRow());
					} catch (ClassNotFoundException | IOException | InvalidIDException e1) {
						e1.printStackTrace();
					}
				}
				
				else {
					JOptionPane.showMessageDialog(contentPane, "Debes seleccionar un colectivo");
					return;
				}
			}
				
				
				
		});

		perfil.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Perfil");
			}
		});
		
		

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
				catch (Exception e1) {
					e1.printStackTrace();
				}
			}
		});

		jp.setVisible(true);
		jp.setSize(300, 300);

		return jp;
	}

	public JPanel perfil(CardLayout cardlayout, Container contentPane)
			throws ClassNotFoundException, IOException, InvalidIDException {
		final Sistema sistema;
		sistema = Sistema.getInstancia();
		if ((user = sistema.usuarioLogin()) == null) {
			user = sistema.logIn("JuanMoreno", "usuario1");
		}

		/* Labels para el logo de la aplicación y el mensaje de bienvenida */
		JLabel picLabel = new JLabel(new ImageIcon(ImageIO.read(new File(".." + File.separator + "Tidea"
				+ File.separator + "src" + File.separator + "Application" + File.separator + "logo.jpeg"))));
		JLabel welcome = new JLabel("Bienvenido " + sistema.usuarioLogin().getNombre() + "!");
		welcome.setFont(new Font("Arial", Font.BOLD, 20));
		welcome.setHorizontalAlignment(SwingConstants.RIGHT);

		/* panel a devolver */
		JPanel jp = new JPanel();
		jp.setName("Tidea");
		jp.setLayout(new BorderLayout());
		jp.setBackground(new Color(236, 247, 231));

		/* panel para ajustar elementos a la izquierda */
		JPanel jpL = new JPanel();
		jpL.setLayout(new BoxLayout(jpL, BoxLayout.Y_AXIS));
		jpL.setBorder(new EmptyBorder(10, 10, 10, 10));
		jpL.setBackground(new Color(236, 247, 231));

		/* panel para ajustar elementos al centro */
		JPanel jpC = new JPanel();
		jpC.setLayout(new BoxLayout(jpC, BoxLayout.Y_AXIS));
		jpC.setBorder(new EmptyBorder(10, 10, 10, 10));
		jpC.setBackground(new Color(236, 247, 231));

		/* panel para ajustar elementos al centro */
		JPanel jpN = new JPanel();
		jpN.setLayout(new BoxLayout(jpN, BoxLayout.X_AXIS));
		jpN.setBorder(new EmptyBorder(10, 10, 10, 10));
		jpN.setBackground(new Color(236, 247, 231));

		JPanel jpMini = new JPanel();
		jpMini.setLayout(new BoxLayout(jpMini, BoxLayout.X_AXIS));
		jpMini.setBackground(new Color(236, 247, 231));

		/* creación y personalización de botones de este panel */
		home = new JButton("Home");
		home.setBackground(new Color(150, 255, 150));
		home.setMaximumSize(new Dimension(100, 35));
		home.setFont(new Font("Arial", Font.PLAIN, 16));
		home.setBorder(new LineBorder(Color.BLACK));

		proyectos = new JButton("Proyectos");
		proyectos.setBackground(new Color(150, 255, 150));
		proyectos.setMaximumSize(new Dimension(125, 35));
		proyectos.setFont(new Font("Arial", Font.PLAIN, 16));

		colectivos = new JButton("Colectivos");
		colectivos.setBackground(new Color(150, 255, 150));
		colectivos.setMaximumSize(new Dimension(125, 35));
		colectivos.setFont(new Font("Arial", Font.PLAIN, 16));

		logOut = new JButton("Cerrar Sesión");
		logOut.setBackground(new Color(150, 255, 150));
		logOut.setMaximumSize(new Dimension(150, 35));
		logOut.setFont(new Font("Arial", Font.BOLD, 16));

		misproyectos = new JButton("Mis Proyectos");
		misproyectos.setBackground(new Color(150, 255, 150));
		misproyectos.setMaximumSize(new Dimension(150, 70));
		misproyectos.setFont(new Font("Arial", Font.PLAIN, 18));

		miscolectivos = new JButton("Mis Colectivos");
		miscolectivos.setBackground(new Color(150, 255, 150));
		miscolectivos.setMaximumSize(new Dimension(150, 70));
		miscolectivos.setFont(new Font("Arial", Font.PLAIN, 18));

		perfil = new JButton("Perfil");
		perfil.setFont(new Font("Arial", Font.PLAIN, 18));
		perfil.setBackground(new Color(127, 232, 84));
		perfil.setMaximumSize(new Dimension(120, 70));

		crearProyectoInfra = new JButton("Crear Proyecto Infraestructura");
		crearProyectoInfra.setFont(new Font("Arial", Font.PLAIN, 18));
		crearProyectoInfra.setBackground(new Color(50, 20, 150));
		crearProyectoInfra.setMaximumSize(new Dimension(300, 50));
		crearProyectoInfra.setForeground(Color.WHITE);

		crearProyectoSoc = new JButton("Crear Proyecto Social");
		crearProyectoSoc.setFont(new Font("Arial", Font.PLAIN, 18));
		crearProyectoSoc.setBackground(new Color(50, 20, 150));
		crearProyectoSoc.setMaximumSize(new Dimension(300, 50));
		crearProyectoSoc.setForeground(Color.WHITE);

		crearColectivo = new JButton("Crear Colectivo");
		crearColectivo.setFont(new Font("Arial", Font.PLAIN, 18));
		crearColectivo.setBackground(new Color(50, 20, 150));
		crearColectivo.setMaximumSize(new Dimension(180, 50));
		crearColectivo.setForeground(Color.WHITE);

		/* añadir los botones en los paneles que queremos */

		jpL.add(welcome);
		jpL.add(Box.createRigidArea(new Dimension(15, 80)));
		jpL.add(home);
		jpL.add(Box.createRigidArea(new Dimension(15, 15)));
		jpL.add(proyectos);
		jpL.add(Box.createRigidArea(new Dimension(15, 15)));
		jpL.add(colectivos);
		jpL.add(Box.createRigidArea(new Dimension(15, 190)));
		jpL.add(logOut);

		jpN.add(picLabel);
		jpN.add(Box.createRigidArea(new Dimension(200, 0)));
		jpN.add(misproyectos);
		jpN.add(Box.createRigidArea(new Dimension(50, 0)));
		jpN.add(miscolectivos);
		jpN.add(Box.createRigidArea(new Dimension(300, 0)));
		jpN.add(perfil);

		JLabel NIF = new JLabel("NIF del usuario: " + sistema.usuarioLogin().getNIF());
		NIF.setFont(new Font("Times New Roman", Font.PLAIN, 20));
		NIF.setHorizontalAlignment(SwingConstants.RIGHT);
		JLabel passw = new JLabel("Contraseña:  " + sistema.usuarioLogin().getPassword());
		passw.setFont(new Font("Times New Roman", Font.PLAIN, 20));
		passw.setHorizontalAlignment(SwingConstants.RIGHT);
		JLabel nombre = new JLabel(sistema.usuarioLogin().getNombre());
		nombre.setFont(new Font("Times New Roman", Font.BOLD | Font.ITALIC, 26));
		nombre.setHorizontalAlignment(SwingConstants.RIGHT);
		nombre.setForeground(new Color(34, 139, 34));

		jpMini.add(crearProyectoInfra);
		jpMini.add(Box.createRigidArea(new Dimension(20, 0)));
		jpMini.add(crearProyectoSoc);

		jpC.setBorder(BorderFactory.createMatteBorder(6, 6, 6, 6, Color.BLACK));
		jpC.add(Box.createRigidArea(new Dimension(15, 10)));
		jpC.add(nombre);
		jpC.add(Box.createRigidArea(new Dimension(15, 40)));
		jpC.add(NIF);
		jpC.add(Box.createRigidArea(new Dimension(15, 20)));
		jpC.add(passw);
		jpC.add(Box.createRigidArea(new Dimension(15, 150)));
		jpC.add(jpMini);
		jpC.add(Box.createRigidArea(new Dimension(15, 20)));
		jpC.add(crearColectivo);

		JPanel jpE = new JPanel();
		jpE.setLayout(new BoxLayout(jpE, BoxLayout.Y_AXIS));
		jpE.setBorder(new EmptyBorder(10, 10, 10, 10));
		jpE.setVisible(false);
		jpE.setBackground(new Color(236, 247, 231));

		JLabel colecNom = new JLabel("Nombre del proyecto:  " + sistema.usuarioLogin().getPassword());
		colecNom.setFont(new Font("Times New Roman", Font.PLAIN, 18));
		colecNom.setHorizontalAlignment(SwingConstants.RIGHT);

		jpE.add(colecNom);

		jp.add(jpC, BorderLayout.CENTER);
		jp.add(jpL, BorderLayout.WEST);
		jp.add(jpN, BorderLayout.NORTH);
		jp.add(jpE, BorderLayout.EAST);

		home.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Inicio");
			}
		});

		misproyectos.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Mis Proyectos");
			}
		});

		proyectos.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Proyectos");
			}
		});

		colectivos.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Colectivos");
			}
		});

		miscolectivos.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Mis Colectivos");
			}
		});

		perfil.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CardLayout showPanel = (CardLayout) contentPane.getLayout();
				showPanel.show(contentPane, "Perfil");
			}
		});

		JPanel jpD = new JPanel();
		jpD.setLayout(new BoxLayout(jpD, BoxLayout.Y_AXIS));
		jpD.setBackground(new Color(236, 247, 231));

		crearProyectoInfra.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				/* Label for NIF in LogIn */
				JLabel tituloLabel = new JLabel("Titulo del Proyecto", JLabel.TRAILING);
				
				combo = new JComboBox<String>();
				combo.setMaximumSize(new Dimension(100, 100));

				for (Distrito d : sistema.getDistritos()) {
					combo.addItem(d.getNombre());
				}
			
				JTextField tituloText = new JTextField(10);
				tituloLabel.setLabelFor(tituloText);
				tituloText.setMaximumSize(new Dimension(400, 30));
				tituloText.setAlignmentX(Component.LEFT_ALIGNMENT);

				/* Label for password in LogIn */
				JLabel descrLabel = new JLabel("Descripción del proyecto", JLabel.TRAILING);

				JTextArea descrText = new JTextArea();
				descrLabel.setLabelFor(descrText);
				descrText.setMaximumSize(new Dimension(400, 50));
				descrText.setLineWrap(true);
				descrText.setAlignmentX(Component.LEFT_ALIGNMENT);

				JLabel importeLabel = new JLabel("Importe solicitado para el proyecto", JLabel.TRAILING);

				JTextField importeText = new JTextField(10);
				importeLabel.setLabelFor(importeText);
				importeText.setMaximumSize(new Dimension(400, 30));
				importeText.setAlignmentX(Component.LEFT_ALIGNMENT);
				
				JLabel afectadosLabel = new JLabel("Distrito afectado", JLabel.TRAILING);

				JLabel imagenLabel = new JLabel("Imagen para el Proyecto", JLabel.TRAILING);

				JFileChooser fileChooser = new JFileChooser();

				imagen = new JButton("Seleccionar imagen");
				imagen.setFont(new Font("Arial", Font.PLAIN, 14));
				imagen.setBackground(new Color(50, 20, 150));
				imagen.setMaximumSize(new Dimension(200, 35));
				imagen.setForeground(Color.WHITE);

				imagen.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						fileChooser.showOpenDialog(fileChooser);
						ruta = fileChooser.getSelectedFile().getAbsolutePath();
					}
				});
				;

				try {
					goBackButton = new JButton(
							new ImageIcon(ImageIO.read(new File(".." + File.separator + "Tidea" + File.separator + "src"
									+ File.separator + "Application" + File.separator + "goback.png"))));
					goBackButton.setMaximumSize(new Dimension(65, 65));
				} catch (IOException e1) {
					e1.printStackTrace();
				}
				goBackButton.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						jpD.removeAll();
						jpC.setVisible(true);
					}
				});

				crearProyectoInfraFinal = new JButton("Crear Proyecto");
				crearProyectoInfraFinal.setFont(new Font("Arial", Font.PLAIN, 14));
				crearProyectoInfraFinal.setBackground(new Color(200, 20, 20));
				crearProyectoInfraFinal.setMaximumSize(new Dimension(200, 35));
				crearProyectoInfraFinal.setForeground(Color.WHITE);
			
				crearProyectoInfraFinal.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						ArrayList<Distrito> afectadosProyecto = new ArrayList<>();
						
						for (Distrito d : sistema.getDistritos()) {
							if (d.getNombre().equals(combo.getSelectedItem())) {
								afectadosProyecto.add(d);
							}
						}
						
						if (tituloText.getText() == null || descrText.getText() == null || importeText.getText() == null
								|| ruta == null) {
							JOptionPane.showMessageDialog(contentPane, "Campo Obligatorio sin rellenar!");
							return;
						} else {
							double importe = Double.parseDouble(importeText.getText());
							try {
								if (sistema.crearProyectoInfraestructura(user, tituloText.getText(), descrText.getText(), importe, ruta, afectadosProyecto) != null) {
									JOptionPane.showMessageDialog(contentPane, "Proyecto creado correctamente!");
									return;
								}
							} catch (ClassNotFoundException | IOException | InvalidIDException e1) {
								e1.printStackTrace();
							}
						}
					}
				});

				jpC.setVisible(false);
				jpD.add(tituloLabel);
				jpD.add(tituloText);
				jpD.add(Box.createRigidArea(new Dimension(15, 15)));
				jpD.add(descrLabel);
				jpD.add(descrText);
				jpD.add(Box.createRigidArea(new Dimension(15, 15)));
				jpD.add(importeLabel);
				jpD.add(importeText);
				jpD.add(Box.createRigidArea(new Dimension(15, 15)));
				jpD.add(imagenLabel);
				jpD.add(imagen);
				jpD.add(Box.createRigidArea(new Dimension(15, 15)));
				jpD.add(afectadosLabel);
				jpD.add(combo);
				jpD.add(Box.createRigidArea(new Dimension(15, 100)));
				jpD.add(crearProyectoInfraFinal, BorderLayout.WEST);
				jpD.add(Box.createRigidArea(new Dimension(15, 15)));
				jpD.add(goBackButton, BorderLayout.WEST);

				jp.add(jpD, BorderLayout.CENTER);
			}
		});

		crearProyectoSoc.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				JLabel tituloLabel = new JLabel("Titulo del Proyecto", JLabel.TRAILING);

				JTextField tituloText = new JTextField(10);
				tituloLabel.setLabelFor(tituloText);
				tituloText.setMaximumSize(new Dimension(400, 30));
				tituloText.setAlignmentX(Component.LEFT_ALIGNMENT);

				JLabel descrLabel = new JLabel("Descripción del proyecto", JLabel.TRAILING);

				JTextArea descrText = new JTextArea();
				descrLabel.setLabelFor(descrText);
				descrText.setMaximumSize(new Dimension(400, 50));
				descrText.setLineWrap(true);
				descrText.setAlignmentX(Component.LEFT_ALIGNMENT);

				JLabel importeLabel = new JLabel("Importe solicitado para el proyecto", JLabel.TRAILING);

				JTextField importeText = new JTextField(10);
				importeLabel.setLabelFor(importeText);
				importeText.setMaximumSize(new Dimension(400, 30));
				importeText.setAlignmentX(Component.LEFT_ALIGNMENT);

				JLabel descrSocLabel = new JLabel("Descripción Social del Proyecto", JLabel.TRAILING);

				JTextArea descrSocText = new JTextArea();
				descrSocLabel.setLabelFor(descrSocText);
				descrSocText.setMaximumSize(new Dimension(400, 50));
				descrSocText.setLineWrap(true);
				descrSocText.setAlignmentX(Component.LEFT_ALIGNMENT);

				JLabel esNacionalLabel = new JLabel("¿Es nacional? (SI ó NO)", JLabel.TRAILING);

				JTextField esNacionalText = new JTextField(10);
				esNacionalLabel.setLabelFor(esNacionalText);
				esNacionalText.setMaximumSize(new Dimension(400, 30));
				esNacionalText.setAlignmentX(Component.LEFT_ALIGNMENT);

				try {
					goBackButton = new JButton(
							new ImageIcon(ImageIO.read(new File(".." + File.separator + "Tidea" + File.separator + "src"
									+ File.separator + "Application" + File.separator + "goback.png"))));
					goBackButton.setMaximumSize(new Dimension(65, 65));
				} catch (IOException e1) {
					e1.printStackTrace();
				}
				goBackButton.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						jpD.removeAll();
						jpC.setVisible(true);
					}
				});

				crearProyectoSocFinal = new JButton("Crear Proyecto");
				crearProyectoSocFinal.setFont(new Font("Arial", Font.PLAIN, 14));
				crearProyectoSocFinal.setBackground(new Color(230, 20, 20));
				crearProyectoSocFinal.setMaximumSize(new Dimension(200, 35));
				crearProyectoSocFinal.setForeground(Color.WHITE);

				crearProyectoSocFinal.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						if (tituloText.getText().equals("") || descrText.getText().equals("") || importeText.getText().equals("")
								|| descrSocText.getText().equals("") || esNacionalText.getText().equals("")) {
							JOptionPane.showMessageDialog(contentPane, "Campo Obligatorio sin rellenar!");
							return;
						} else {
							double importe = Double.parseDouble(importeText.getText());
							if (esNacionalText.getText().equals("SI")) {
								try {
									if (sistema.crearProyectoSocial(user, tituloText.getText(), descrText.getText(), importe, descrSocText.getText(), true) != null) {
										JOptionPane.showMessageDialog(contentPane, "Proyecto creado correctamente!");
										return;
									}
								} catch (ClassNotFoundException | IOException | InvalidIDException e1) {
									e1.printStackTrace();
								}
							} else {
								try {
									if (sistema.crearProyectoSocial(user, tituloText.getText(), descrText.getText(),importe, descrSocText.getText(), false) != null) {
										JOptionPane.showMessageDialog(contentPane, "Proyecto creado correctamente!");
										return;
									}
								} catch (ClassNotFoundException | IOException | InvalidIDException e1) {
									e1.printStackTrace();
								}
							}
						}
					}
				});

				jpC.setVisible(false);

				jpD.add(tituloLabel);
				jpD.add(tituloText);
				jpD.add(Box.createRigidArea(new Dimension(15, 15)));
				jpD.add(descrLabel);
				jpD.add(descrText);
				jpD.add(Box.createRigidArea(new Dimension(15, 15)));
				jpD.add(importeLabel);
				jpD.add(importeText);
				jpD.add(Box.createRigidArea(new Dimension(15, 15)));
				jpD.add(descrSocLabel);
				jpD.add(descrSocText);
				jpD.add(Box.createRigidArea(new Dimension(15, 15)));
				jpD.add(esNacionalLabel);
				jpD.add(esNacionalText);
				jpD.add(Box.createRigidArea(new Dimension(15, 100)));
				jpD.add(crearProyectoSocFinal, BorderLayout.WEST);
				jpD.add(Box.createRigidArea(new Dimension(15, 15)));
				jpD.add(goBackButton, BorderLayout.WEST);

				jp.add(jpD, BorderLayout.CENTER);
			}
		});

		crearColectivo.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				/* Label for NIF in LogIn */
				JLabel nombreColLabel = new JLabel("Nombre del Colectivo", JLabel.TRAILING);

				JTextField nombreColText = new JTextField(10);
				nombreColLabel.setLabelFor(nombreColText);
				nombreColText.setMaximumSize(new Dimension(400, 30));
				nombreColText.setAlignmentX(Component.LEFT_ALIGNMENT);
				
				try {
					goBackButton = new JButton(
							new ImageIcon(ImageIO.read(new File(".." + File.separator + "Tidea" + File.separator + "src"
									+ File.separator + "Application" + File.separator + "goback.png"))));
					goBackButton.setMaximumSize(new Dimension(65, 65));
				} catch (IOException e1) {
					e1.printStackTrace();
				}
				goBackButton.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						jpD.removeAll();
						jpC.setVisible(true);
					}
				});

				crearColectivoFinal = new JButton("Crear Colectivo");
				crearColectivoFinal.setFont(new Font("Arial", Font.PLAIN, 14));
				crearColectivoFinal.setBackground(new Color(230, 20, 20));
				crearColectivoFinal.setMaximumSize(new Dimension(200, 35));
				crearColectivoFinal.setForeground(Color.WHITE);

				crearColectivoFinal.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						if (nombreColText.getText().equals("")) {
							JOptionPane.showMessageDialog(contentPane, "Campo Obligatorio sin rellenar!");
							return;
						} else {
							try {
								if (user.crearColectivo(nombreColText.getText()) != null) {
									JOptionPane.showMessageDialog(contentPane, "Colectivo creado correctamente!");
									return;
								}
							} catch (ClassNotFoundException | IOException | InvalidIDException e1) {
								e1.printStackTrace();
							}
						}
					}
				});

				jpC.setVisible(false);

				jpD.add(nombreColLabel);
				jpD.add(nombreColText);

				jpD.add(Box.createRigidArea(new Dimension(15, 100)));
				jpD.add(crearColectivoFinal, BorderLayout.WEST);
				jpD.add(Box.createRigidArea(new Dimension(15, 15)));
				jpD.add(goBackButton, BorderLayout.WEST);

				jp.add(jpD, BorderLayout.CENTER);
			}
		});

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
				} catch (Exception e1) {
					e1.printStackTrace();
				}
			}
		});

		jp.setVisible(true);

		return jp;
	}

	public MainPage() throws Exception {
		super("Tidea");

		final CardLayout cardlayout = new CardLayout();

		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setSize(1280, 720);
		this.setVisible(true);

		final Container contentPane = this.getContentPane();
		contentPane.setLayout(cardlayout);

		final JPanel Home = this.Home(cardlayout, contentPane);
		final JPanel tablaProyectos = this.proyectos(cardlayout, contentPane);
		final JPanel tablaColectivos = this.colectivos(cardlayout, contentPane);
		final JPanel misColectivos = this.misColectivos(cardlayout, contentPane);
		final JPanel perfil = this.perfil(cardlayout, contentPane);
		final JPanel misProyectos = this.misProyectos(cardlayout, contentPane);

		contentPane.setPreferredSize(new Dimension(1280, 720));
		contentPane.add(Home, "Inicio");
		contentPane.add(tablaProyectos, "Proyectos");
		contentPane.add(tablaColectivos, "Colectivos");
		contentPane.add(misColectivos, "Mis Colectivos");
		contentPane.add(perfil, "Perfil");
		contentPane.add(misProyectos, "Mis Proyectos");

		this.pack();
		this.setLocationRelativeTo(null);
		this.setResizable(true);
	}

	public static void main(String[] args) throws Exception {
		new MainPage();
	}

}

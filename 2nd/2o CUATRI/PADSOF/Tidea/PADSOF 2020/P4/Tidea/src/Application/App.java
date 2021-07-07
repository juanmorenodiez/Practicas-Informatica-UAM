package Application;

import java.awt.BorderLayout;
import java.awt.CardLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.HeadlessException;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.*;

import Sistemas.Sistema;
import Usuarios.Usuario;
import es.uam.eps.sadp.grants.InvalidIDException;

public class App extends JFrame {
	private static final long serialVersionUID = 1L;

	private final Sistema sistema = Sistema.getInstancia();

	/**
	 * Crear el panel de inicio de la aplicacion, en el que se podra introducir a la aplicacion si se esta
	 * registrado
	 * @param cardlayout para organizar los paneles y saber cual se muestra.
	 * @param contentPane en el panel en el que se encuentra.
	 * @return JPanel inicial.
	 * @throws IOException excepcion.
	 */
	public JPanel TideaLogin(CardLayout cardlayout, Container contentPane) throws IOException {
		String[] labelsLogIn = { "NIF o Nombre de Usuario:", "Password:" };
		
		/** Creacion panel principal y paneles secundarios */
		JPanel jp = new JPanel();
		jp.setName("Tidea");
		jp.setBackground(new Color(236, 247, 231));
		
		/** Creacion de un BoxLayOut para tener los botones en una sola columna*/
		JPanel jpINI = new JPanel();
		jpINI.setLayout(new BoxLayout(jpINI, BoxLayout.Y_AXIS));
		jp.add(jpINI, BorderLayout.CENTER);
		jpINI.setBackground(new Color(236, 247, 231));

		/** Logo que se muestra al inicio*/
		JLabel logo = new JLabel(new ImageIcon(ImageIO.read(new File(".." + File.separator + "Tidea" + File.separator
				+ "src" + File.separator + "Application" + File.separator + "logo.jpeg"))));
		jpINI.add(logo);
		
		/** Label for NIF in LogIn */
		JLabel NIFLoginLabel = new JLabel(labelsLogIn[0], JLabel.TRAILING);
		NIFLoginLabel.setFont(new Font("Arial", Font.PLAIN, 20));
		jpINI.add(NIFLoginLabel);
		JTextField NIFLogIn = new JTextField(10);
		NIFLoginLabel.setLabelFor(NIFLogIn);
		NIFLogIn.setFont(new Font("Arial", Font.PLAIN, 22));
		NIFLogIn.setMaximumSize(new Dimension(500, 70));
		jpINI.add(NIFLogIn);
		
		/** Label for password in LogIn */
		JLabel passLoginLabel = new JLabel(labelsLogIn[1], JLabel.TRAILING);
		passLoginLabel.setFont(new Font("Arial", Font.PLAIN, 22));
		jpINI.add(passLoginLabel);
		JTextField passLogIn = new JPasswordField(10);
		passLoginLabel.setLabelFor(passLogIn);
		passLogIn.setFont(new Font("Arial", Font.PLAIN, 26));
		passLogIn.setMaximumSize(new Dimension(500, 70));
		jpINI.add(passLogIn);
		
		/** Label for ini */
		JButton iniciar = new JButton("Iniciar Sesi�n");
		iniciar.setFont(new Font("Arial", Font.PLAIN, 26));
		iniciar.setBackground(new Color(150, 255, 150));
		iniciar.setMaximumSize(new Dimension(300, 70));
		jpINI.add(iniciar);
		
		/** Label for register */
		JButton registrar = new JButton("Registrarse");
		registrar.setFont(new Font("Arial", Font.PLAIN, 26));
		registrar.setBackground(new Color(150, 255, 150));
		registrar.setMaximumSize(new Dimension(300, 70));
		jpINI.add(registrar);
		
		/**Anadimos los margenes entre los botones*/
		jpINI.add(Box.createRigidArea(new Dimension(0, 20)));
		jpINI.add(iniciar, BorderLayout.NORTH);
		jpINI.add(Box.createRigidArea(new Dimension(0, 20)));
		jpINI.add(registrar, BorderLayout.SOUTH);
		
		/**Accion para ir a la pagina de registro*/
		registrar.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				cardlayout.show(contentPane, "Registro");
			}
		});
		
		/**Accion para poder hacer logIn en la aplicacion*/
		iniciar.addActionListener(new ActionListener() {
			@Override

			public void actionPerformed(ActionEvent e) {
				if (sistema.usuarioLogin() != null) {
					JOptionPane.showMessageDialog(contentPane,
							"Lo sentimos, ya hay un usuario LogIn en la aplicacion, vuelva mas tarde");
					return;
				} else {
					try {
						if (sistema.logIn(NIFLogIn.getText(), passLogIn.getText()) == null) {
							JOptionPane.showMessageDialog(contentPane,
									"Usuario o contrase�a incorrectos o usuario bloqueado");
							return;
						}
					} catch (HeadlessException | ClassNotFoundException | IOException | InvalidIDException e2) {
						// TODO Auto-generated catch block
						e2.printStackTrace();
					}
					if (sistema.usuarioLogin().equals(sistema.getAdmin())) {
						try {
							JFrame topFrame = (JFrame) SwingUtilities.getWindowAncestor(jp);
							topFrame.dispose();
							new Admin();
						} catch (Exception e1) {
							// TODO Auto-generated catch block
							e1.printStackTrace();
						}
					} else if ((sistema.usuarioLogin().getNIF().equals(NIFLogIn.getText()))
							|| (sistema.usuarioLogin().getNombre().equals(NIFLogIn.getText()))
									&& sistema.usuarioLogin().getPassword().equals(passLogIn.getText())) {
						try {
							JFrame topFrame = (JFrame) SwingUtilities.getWindowAncestor(jp);
							topFrame.dispose();
							new MainPage();
						} catch (Exception e1) {
							// TODO Auto-generated catch block
							e1.printStackTrace();
						}
					}
				}
			}
		});
		
		/**Tamano del panel y visible porque es el primero*/
		jp.setVisible(true);
		jp.setSize(300, 300);
		return jp;
	}

	/**
	 * Crear el panel de registro para que los usuarios se puedan registrar 
	 * para poder usar la aplicacion.
	 * @param cardlayout para organizar los paneles y saber cual se muestra.
	 * @param contentPane Panel en el que esta contenido.
	 * @return Jpanel
	 * @throws IOException excepcion.
	 */
	public JPanel TideaRegister(CardLayout cardlayout, Container contentPane) throws IOException {
		String[] labelsRegister = { "Username:", "NIF: ", "Password" };

		/** Creacion panel principal y paneles secundarios */
		JPanel jp = new JPanel();
		jp.setName("Tidea");

		/** Creacion de un BoxLayOut para tener los botones en una sola columna*/
		JPanel jpREG = new JPanel();
		jpREG.setLayout(new BoxLayout(jpREG, BoxLayout.Y_AXIS));
		jp.add(jpREG, BorderLayout.CENTER);


		/** Logo que se muestra al inicio*/
		JLabel logo = new JLabel(new ImageIcon(ImageIO.read(new File(".." + File.separator + "Tidea" + File.separator
				+ "src" + File.separator + "Application" + File.separator + "logo.jpeg"))));
		jpREG.add(logo);

		/** Label for username in LogIn */
		JLabel usernameRegLabel = new JLabel(labelsRegister[0], JLabel.TRAILING);
		usernameRegLabel.setFont(new Font("Arial", Font.PLAIN, 26));
		jpREG.add(usernameRegLabel);
		JTextField usernameReg = new JTextField(10);
		usernameReg.setFont(new Font("Arial", Font.PLAIN, 26));
		usernameReg.setMaximumSize(new Dimension(500, 70));
		usernameRegLabel.setLabelFor(usernameReg);
		jpREG.add(usernameReg);

		/** Label for NIF in Register */
		JLabel NIFRegLabel = new JLabel(labelsRegister[1], JLabel.TRAILING);
		NIFRegLabel.setFont(new Font("Arial", Font.PLAIN, 26));
		jpREG.add(NIFRegLabel);
		JTextField NIFreg = new JTextField(10);
		NIFRegLabel.setLabelFor(NIFreg);
		NIFreg.setFont(new Font("Arial", Font.PLAIN, 26));
		NIFreg.setMaximumSize(new Dimension(500, 70));
		jpREG.add(NIFreg);

		/** Label for password in Register */
		JLabel passRegLabel = new JLabel(labelsRegister[2], JLabel.TRAILING);
		passRegLabel.setFont(new Font("Arial", Font.PLAIN, 26));
		jpREG.add(passRegLabel);
		JTextField passReg = new JPasswordField(10);
		passReg.setFont(new Font("Arial", Font.PLAIN, 26));
		passReg.setMaximumSize(new Dimension(500, 70));
		passRegLabel.setLabelFor(passReg);
		jpREG.add(passReg);

		/**Boton de registrarse al haber introducido los datos*/
		JButton terminarReg = new JButton("Registrarme");
		terminarReg.setFont(new Font("Arial", Font.PLAIN, 26));
		terminarReg.setBackground(new Color(150, 255, 150));
		terminarReg.setMaximumSize(new Dimension(500, 70));
		jpREG.add(terminarReg);
		
		/**Bordes para separar algunos botones.*/
		jpREG.add(Box.createRigidArea(new Dimension(0, 20)));
		jpREG.add(terminarReg, BorderLayout.SOUTH);

		/**Accion al clickar en el boton de registrarse para completar el registro*/
		terminarReg.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				int flag = 0;
				for (Usuario u : sistema.getUsuarios()) {
					if (u.getNIF().equals(NIFRegLabel.getText())) {
						flag = 1;
						break;
					}
					if (u.getNombre().equals(usernameReg.getText())) {
						flag = 2;
						break;
					}
				}
				if (flag == 1) {
					JOptionPane.showMessageDialog(contentPane,
							"Lo sentimos, el NIF: " + NIFRegLabel.getText()
									+ " ya esta en la lista de usuarios, intentelo de nuevo por favor",
							"Error", JOptionPane.ERROR_MESSAGE);
					return;
				} else if (flag == 2) {
					JOptionPane.showMessageDialog(contentPane,
							"Lo sentimos, el Nombre: " + usernameReg.getText()
									+ " ya esta en la lista de usuarios, intentelo de nuevo por favor",
							"Error", JOptionPane.ERROR_MESSAGE);
					return;
				} else if (NIFRegLabel.getText() == "") {
					JOptionPane.showMessageDialog(contentPane, "Debes introducir un NIF valido", "Error",
							JOptionPane.ERROR_MESSAGE);
					return;
				} else if (usernameReg.getText() == " ") {
					JOptionPane.showMessageDialog(contentPane, "Debe introducir un user name valido", "Error",
							JOptionPane.ERROR_MESSAGE);
					return;
				} else if (passRegLabel.getText() == " ") {
					JOptionPane.showMessageDialog(contentPane, "Debe introducir una contrasena valida", "Error",
							JOptionPane.ERROR_MESSAGE);
					return;
				} else {
					sistema.registrarse(usernameReg.getText(), NIFRegLabel.getText(), passReg.getText());
					cardlayout.show(contentPane, "Inicio");
				}
			}
		});
		
		/**Actualizamos la visibilidad y el tamano*/
		jp.setVisible(true);
		jp.setSize(300, 300);
		return jp;
	}

	/**
	 * Desde aqui se carga toda la interfaz llamando a todos los metodos para que se ejecuten.
	 * @throws Exception excepcion.
	 */
	public App() throws Exception {
		super("Tidea");

		/**Creamos el CardLayout*/
		final CardLayout cardlayout = new CardLayout();

		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setSize(1280, 720);
		this.setVisible(true);

		final Container contentPane = this.getContentPane();
		contentPane.setLayout(cardlayout);

		/**Llamamos a los metodos para cargar el inicio y la pagina de registrarse*/
		final JPanel jpInicio = this.TideaLogin(cardlayout, contentPane);
		final JPanel jpRegistro = this.TideaRegister(cardlayout, contentPane);

		contentPane.setPreferredSize(new Dimension(1280, 720));
		contentPane.add(jpInicio, "Inicio");
		contentPane.add(jpRegistro, "Registro");
		this.pack();
		this.setLocationRelativeTo(null);
		this.setResizable(true);
	}

	/**
	 * Cargamos toda la aplicacion automaticamente llamando al metodo APP()
	 * @param args argumentos de entrada.
	 * @throws Exception excepcion.
	 */
	public static void main(String[] args) throws Exception {

		new App();
	}
}

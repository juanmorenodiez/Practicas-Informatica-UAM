package Application;

import java.awt.BorderLayout;
import java.awt.CardLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

import javax.swing.*;

import Sistemas.Sistema;
import Usuarios.Usuario;
import es.uam.eps.sadp.grants.InvalidIDException;

public class App extends JFrame {
	private static final long serialVersionUID = 1L;

	public static void main(String[] args) throws Exception {
		final Sistema sistema;
		String[] labelsLogIn = {"NIF:", "Password"};
		String[] labelsRegister = {"Username:","NIF: ", "Password"};
		
		
		sistema = Sistema.getInstancia();
		
		System.out.println(sistema.getProyectos());

		JFrame ventana = new JFrame("Tidea");
		
		Container contenedor = ventana.getContentPane();
		contenedor.setLayout(new FlowLayout());
		
/********************************************************/
		JPanel inicio = new JPanel();
		
		/* Label for NIF in LogIn */
		JLabel NIFLoginLabel = new JLabel(labelsLogIn[0], JLabel.TRAILING);
		NIFLoginLabel.setBounds(10, 10, 80, 25);
		inicio.add(NIFLoginLabel);
		
		JTextField NIFLogIn = new JTextField(10);
		NIFLogIn.setBounds(100, 10, 160, 25);
		NIFLoginLabel.setLabelFor(NIFLogIn);
		inicio.add(NIFLogIn);
		
		/* Label for password in LogIn */
		JLabel passLoginLabel = new JLabel(labelsLogIn[1], JLabel.TRAILING);
		passLoginLabel.setBounds(10, 40, 80, 25);
		inicio.add(passLoginLabel);
		
		JTextField passLogIn = new JTextField(10);
		passLogIn.setBounds(100, 40, 160, 25);
		passLoginLabel.setLabelFor(passLogIn);
		inicio.add(passLogIn);
		
		/* Boton para poder iniciar sesion */
		JButton iniciar = new JButton("Iniciar Sesion");
		inicio.add(iniciar);
		
		/* Boton a la pestana registrarse*/
		JButton registrar = new JButton("Registrarme");
		inicio.add(registrar);
		
		/* Visible porque es la primera */
		inicio.setVisible(true);
		inicio.setSize(300, 300);
		
/********************************************************/
		
		JPanel registP = new JPanel();
		registP.setVisible(false);
	
		
		contenedor.setLayout(new FlowLayout());
		
		/* Label for username in LogIn */
		JLabel usernameRegLabel = new JLabel(labelsRegister[0], JLabel.TRAILING);
		registP.add(usernameRegLabel);
		JTextField usernameReg = new JTextField(10);
		usernameRegLabel.setLabelFor(usernameReg);
		registP.add(usernameReg);
		
		/* Label for NIF in Register */
		JLabel NIFRegLabel = new JLabel(labelsRegister[1], JLabel.TRAILING);
		registP.add(NIFRegLabel);
		JTextField NIFreg = new JTextField(10);
		NIFRegLabel.setLabelFor(NIFreg);
		registP.add(NIFreg);
		
		/* Label for password in Register */
		JLabel passRegLabel = new JLabel(labelsRegister[2], JLabel.TRAILING);
		registP.add(passRegLabel);
		JTextField passReg = new JPasswordField(10);
		passRegLabel.setLabelFor(passReg);
		registP.add(passReg);
		
		JButton terminarReg = new JButton("Confirmar");
		registP.add(terminarReg);
		
		JButton cancelarReg = new JButton("Cancelar");
		registP.add(cancelarReg);
	
		
/********************************************************/
		JPanel pantalla1 = new JPanel();
		pantalla1.setVisible(false);
		contenedor.setLayout(new FlowLayout());

/********************************************************/		
	
		/*Boton de inicio, registrarse*/
		registrar.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {				
				inicio.setVisible(false);
				registP.setVisible(true);				
				
			}
		});
		
		/*Boton de registrarse, terminar */
		terminarReg.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {				
				inicio.setVisible(true);
				registP.setVisible(false);				
				
				Usuario usuario1 = sistema.registrarse(usernameReg.getText(), NIFreg.getText(), passReg.getText());
				System.out.println(sistema.getUsuarios());
				System.out.println(NIFreg.getText()); 
			}
		});
		
		/**/
		iniciar.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				JLabel etiqueta = new JLabel(sistema.getUsuarios().get(0).getNombre());
				inicio.add(etiqueta, BorderLayout.SOUTH);
			}
		});

		
		/*Comprobar si el usuario accede a la aplicacion*/
			iniciar.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed (ActionEvent e) {
						Usuario usuarioLogIn = sistema.logIn(NIFLogIn.getText(), passLogIn.getText());
						if (sistema.usuarioLogin().getNIF() == NIFLogIn.getText() && sistema.usuarioLogin().getPassword() == passLogIn.getText()) {
							iniciar.setVisible(false);
							pantalla1.setVisible(true);
							JOptionPane.showMessageDialog(null, "hola");
						} else {
							JOptionPane.showMessageDialog(null, "Error al introducir el NIF o la contrasena");
						}
				}
			});
		
		/*Anado las pantallas al contenedor*/
		contenedor.add(inicio);
		contenedor.add(registP);
		contenedor.add(pantalla1);

		/*Muestro la ventana contedor*/
		ventana.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		ventana.setSize(780, 500);
		ventana.setVisible(true);
	}
}

package Testers;

import Usuarios.*;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.Date;

import Proyectos.*;
import Sistemas.*;


public class Main1 {
	public static void main(String[] args) {
		final Sistema s;
		Usuario u1, u2, u3, admin;
		Proyecto p1, p2;
		
		DateFormat dateFormat = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
		Date date = new Date();
		System.out.println(dateFormat.format(date)); //2016/11/16 12:08:43
		
		s = Sistema.getInstancia();
		
		u1 = s.registrarse("11111111", "apersona1");
		u2 = s.registrarse("22222222", "aspersona2");
		/*u3 = s.registrarse("0432642", "coronavirus");*/
		
		System.out.println("Lista al registrar: " + s.getUsuarios());
		
		admin = s.getAdmin();
		
		admin.validarUsuario(u1);
		
		System.out.println("Lista al validar u1: " + s.getUsuarios());
		
		s.LogIn(u1.getNIF(), u1.getPassword());
		s.LogIn(u2.getNIF(), u2.getPassword());
		
		System.out.println( "Lista al hacer logIn: " + s.getUsuarios());
		
		u1.crearProyecto("Quedada Corona", "Lo pillamos todos y fuera chavales", date, 5000.25);
		
	}
}

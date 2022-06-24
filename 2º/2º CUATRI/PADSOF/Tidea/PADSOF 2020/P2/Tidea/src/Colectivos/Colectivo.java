package Colectivos;
import java.util.*;
import Usuarios.*;

public class Colectivo {
		private String nombre;
		private Usuario representante;
		private ArrayList<Usuario> integrantesColectivo;
		
		public Colectivo(String nombre, Usuario representante) {
			this.setNombre(nombre);
			this.setRepresentante(representante);
			this.integrantesColectivo = new ArrayList<Usuario>();
		}

		public Usuario getRepresentante() {
			return representante;
		}

		public void setRepresentante(Usuario representante) {
			this.representante = representante;
		}

		public String getNombre() {
			return nombre;
		}

		public void setNombre(String nombre) {
			this.nombre = nombre;
		}

		public ArrayList<Usuario> getIntegrantesColectivo() {
			return integrantesColectivo;
		}
		
		public void unirseColectivo(Usuario usuario) {
			if (usuario == null || this.integrantesColectivo.contains(usuario) || usuario.isLoggedIn() == false || usuario.getTipo() == TipoUsuario.ADMINISTRADOR) {
				return;
			}
			
			this.integrantesColectivo.add(usuario);
		}
		
		public void dejarColectivo(Usuario usuario) {
			if (usuario == null || !this.integrantesColectivo.contains(usuario) || usuario.isLoggedIn() == false || usuario.getTipo() == TipoUsuario.ADMINISTRADOR) {
				return;
			}
			
			this.integrantesColectivo.remove(usuario);
		}
}

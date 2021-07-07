package Notificaciones;

public class Notificacion {
	private String texto;
	private TipoNotificacion tipo;
	
	public Notificacion(String texto, TipoNotificacion tipo) {
		this.texto = texto;
		this.tipo = tipo;
	}
	
	public String getTexto() {
		return texto;
	}
	
	public void setTexto(String texto) {
		this.texto = texto;
	}
	
	public TipoNotificacion getTipo() {
		return tipo;
	}
	
	public void setTipo(TipoNotificacion tipo) {
		this.tipo = tipo;
	}

}

package Notificaciones;

public enum TipoNotificacion {
	PROYECTO(0),
	COLECTIVO(1),
	FINANCIACION(2);
	
	private TipoNotificacion(int v) {
		this.setValor(v);
	}
	
	public int getValor() {
		return valor;
	}

	public void setValor(int valor) {
		this.valor = valor;
	}

	private int valor;

}

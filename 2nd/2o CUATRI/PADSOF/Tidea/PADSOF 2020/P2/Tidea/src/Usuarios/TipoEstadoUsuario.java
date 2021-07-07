package Usuarios;

public enum TipoEstadoUsuario {
	
	BLOQUEADO(0),
	DESBLOQUEADO(1),
	VALIDADO(2),
	RECHAZADO(3),
	PENDIENTEVALIDAR(4);
	
	private TipoEstadoUsuario(int v) {
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

package Usuarios;

public enum TipoUsuario {

	ADMINISTRADOR(0),
	USUARIONOREGISTRADO(1),
	USUARIOREGISTRADO(2);
	
	private TipoUsuario(int v) {
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

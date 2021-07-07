package Proyectos;

public enum TipoEstadoProyecto {

	VALIDADO(0),
	FINANCIADO(1),
	FINANCIACIONSOLICITADA(2),
	PENDIENTEVALIDACION(3);
	
	private TipoEstadoProyecto(int v) {
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

public class Regulagem{

	private class Adubo{
		private String formula;
		private float gramas;

		public void setFormula(String f){ this.formula = f; }
		public void setGramas(float g){ this.gramas = g; }
		public String getFormula(){ return this.formula; }
		public float getGramas(){ return this.gramas; }
	}
	private class Semente{
		private String variedade;
		private float gramas;

		public void setVariedade(String v){ this.variedade = v; }
		public void setGramas(float g){ this.gramas = g; }
		public String getVariedade(){ return this.variedade; }
		public float getGramas(){ return this.gramas; }
		
	}

	private float espacamento, tiro;
	private String cultura;
	private Adubo adb;
	private Semente smt;

	public void setEspc(float e){ this.espacamento = e; }
	public void setTiro(float t){ this.tiro = t; }
	public void setCult(String c){ this.cultura = c; }
	public void setGramAdb(float g){ this.adb.setGramas(g); }
	public void setGramSmt(float g){ this.smt.setGramas(g); }
	public void setFormulaSmt(String f){ this.adb.setFormula(f); }
	public void setVariedadeAdb(String v){ this.smt.setVariedade(v); }

	public String getCultura(){ return this.cultura; }
	public float getEspc(){ return this.espacamento; }
	public float getTiro(){ return this.tiro; }
	public String getFormulaAdb(){ return this.adb.getFormula(); }
	public String getVariedadeSmt(){ return this.smt.getVariedade(); }
	public float getGramAdb(){ return this.adb.getGramas(); }
	public float getGramSmt(){ return this.smt.getGramas(); }
}

/*float calcularGramasTiro(float k, Regulagem* r) {
    return (k * r->getTiro() * r->getEspc()) / 1000.0;
}

std::array<float, 2> calcularQuilosHectare(Regulagem* r) {
    std::array<float, 2> kgha;
    kgha[0] = (r->getGramSmt() * 1000.0) / (r->getEspc() * r->getTiro());
    kgha[1] = (r->getGramAdb() * 1000.0) / (r->getEspc() * r->getTiro());
    return kgha;
}*/

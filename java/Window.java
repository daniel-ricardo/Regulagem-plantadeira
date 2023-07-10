/*
import java.awt.GridBagLayout;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextArea;
*/
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Window extends Regulagem{
	public Regulagem regulagem;
	public float tmp_espc, tmp_tiro, tmp_grm_smt, tmp_grm_adb;
	public String tmp_cult, tmp_form, tmp_vari;

	public static void main(String[] args){
		JFrame Janela = new JFrame("Calculadora para Regulagem de Plantadeira");
        Janela.setSize(500,300);

		JPanel Painel = new JPanel();
        Painel.setSize(300, 300);

		Painel.setLayout(new GridBagLayout());

		JLabel LabelCult = new JLabel();
        LabelCult.setText("Cultura: ");

		Painel.add(LabelCult);
		Janela.add(Painel);
		Janela.setVisible(true);
	}
}

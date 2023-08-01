# Calculadora para fazer regulagem de plantadeira

Colocando as quantidades em quilo por hectare de semente e adubo, o programa vai apresentar as quantidades em gramas para fazer a regulagem numa �rea menor.

*****

## Imagens:
<table>
	<thead>
		<tr>
			<th>Janela padr�o no Windows</th>
			<th>Janela no linux (gerenciador XFCE)</th>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td>
				<img src="assets/latest_win64.png" alt="windows" title="v1.2 no Windows">
			</td>
			<td>
				<img src="assets/latest_linuxXFCE.png" alt="linux" title="v1.3 no Linux">
			</td>
		</tr>
	</tbody>
</table>

*****

## Utiliza��o

Os valores padr�o s�o 17 cent�metros de espa�amento e 25 metros de tiro, mas podem ser alterados.

Colocando quantos hectares ser�o plantados, tamb�m � poss�vel ter uma previs�o do total a ser gasto.

A sele��o de culturas n�o afeta o funcionamento do programa (na vers�o atual).

## O c�lculo:

Os dados necess�rios para realizar o c�lculo:

- *Alvo*: Quantide de quilos a cair por hectare
- *Espa�amento*: Dist�ncia entre uma linha e outra (em cent�metros)
- *Tiro*: Comprimento da �rea de teste

A quantidade que a plantadeira deve soltar na regulagem (em gramas) ser� chamada de *Teste*.

A rela��o entre os dados:

$$ \textrm{Alvo}\ kg \longrightarrow \textrm{1 Hectare}\ m^2 $$

$$ \textrm{Teste} \longrightarrow \textrm{�rea de teste}\ m^2 $$

Aplicando a regra de tr�s, temos a equa��o 1:

$$ \textrm{Teste} \cdot 10000 m^2 = \textrm{Alvo}\ kg  \cdot  \textrm{�rea de teste}\ m^2 $$

Como o espa�amento � medido em cent�metros e o tiro em metros, o valor da �rea de teste tamb�m pode ser descrito como:

$$ \textrm{�rea de teste}\ m^2 = \textrm{Espa�amento}\ cm \cdot \textrm{Tiro}\ m $$

Substituindo na equa��o 1:

$$ \textrm{Teste} \cdot 10000 m^2 = \textrm{Alvo}\ kg \cdot \textrm{Espa�amento}\ cm \cdot \textrm{Tiro}\ m $$

Convertendo o alvo para a unidade de gramas e o espa�amento para metros:

$$ \textrm{Teste} \cdot 10000 m^2 = \textrm{Alvo}\ g \cdot 1000 \cdot { \textrm{Espa�amento} \over 100 } \ m \cdot \textrm{Tiro}\ m $$

Simplificando:

$$ \textrm{Teste} = { \textrm{Alvo} \cdot \textrm{Espa�amento} \cdot \textrm{Tiro} \over 1000 }\ g $$

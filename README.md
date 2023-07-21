# Calculadora para fazer regulagem de plantadeira

Colocando as quantidades em quilo por hectare de semente e adubo, o programa vai apresentar as quantidades em gramas para fazer a regulagem numa  rea menor.

*****

## Imagens:

![v1.1.0 no Windows](v1.1.0_win64.png)<br/>
<b>Janela padr„o no Windows</b>

![v1.1.0 no Windows](v1.1.0_win64_values.png)<br/>
<b>Janela com valores calculados</b>


*****

## O c lculo:

> †rea de teste (hectares) **=** **(** Espa‡amento **x** Tiro **)** **/** 100

Aplicando a regra de trÃƒÂªs:

> Alvo  ? 1 Hectare  
> Teste(?) ?  rea de teste

> Teste **x** 10 000 mý **=** Alvo **x** **(** Espa‡amento **x** Tiro **)** **/** 100

Simplificando:

> Teste **=** ( Alvo **x** Espa‡amento **x** Tiro ) **/** 1000

- *Teste*: Quantidade que a plantadeira deve soltar na regulagem (em gramas)
- *Alvo*: Quilos por hectare
- *Espa‡amento*: Distƒncia entre uma linha e outra (em cent¡metros)
- *Tiro*: Comprimento da  rea de teste

Os valores padr„o s„o 17 cent¡metros de espa‡amento e 25 metros de tiro, mas podem ser alterados.

Colocando quantos hectares ser„o plantados, tamb‚m ‚ poss¡vel ter uma previs„o do total a ser gasto.

A sele‡„o de culturas n„o afeta o funcionamento do programa (na vers„o atual).

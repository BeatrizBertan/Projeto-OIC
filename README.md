# <p align="center"> PROJETO: DETECÇÃO DE VAZAMENTOS ATRAVÉS DE SENSOR DE GÁS </p>

### MENU DE LINKS
<ul>
<li><a href= "https://github.com/BeatrizBertan/Projeto-OIC/blob/main/Projeto.ino">Código do Projeto</a></li>
<li><a href= "https://github.com/BeatrizBertan/Projeto-OIC/blob/main/Projeto.png">Esquema do Projeto </a></li>
<li><a href= "https://github.com/BeatrizBertan/Projeto-OIC/blob/main/Projeto_Esquem%C3%A1tico.png"> Diagrama do Projeto </a></li>
<li><a href= "https://github.com/BeatrizBertan/Projeto-OIC/blob/main/Fluxograma%20do%20Projeto.png">Fluxograma do Projeto </a></li>
</ul>

<br/>

### DESCRIÇÃO 
<p align = "justify">
O projeto é um produto desenvolvido para detectar vazamentos através de um sensor de gás e Nodemcu. A ideia desse projeto foi motivada com os sintomas de falta de olfato que muitas vítimas do Covid-19 estão apresentando nesta época.
</p>
<p align = "justify">
Portanto, ao detectar a presença de gás no ambiente, o protótipo irá acionar um alerta através de um buzzer e impedirá que a lâmpada controlada remotamente por um aplicativo chamado MQTT Dash seja acesa. Por outro lado, caso já esteja acesa, a lâmpada será desligada. Dessa forma, além de avisar ao morador da casa sobre o vazamento, evitará também possíveis acidentes.
</p>

<p align="center"><img src="https://user-images.githubusercontent.com/61274339/119237464-4fa63f00-bb13-11eb-8a85-f62d44c92b3a.jpg"  width="600px" height="400px"/></p>


<br/>

### COMPONENTES UTILIZADOS
<ul>
<li>Nodemcu ESP8266</li>
<li>Cabo USB</li>
<li>Sensor de Gás Inflamável MQ-2</li>
<li>Buzzer Passivo</li>
<li>2 Protoboards Brancos de 830 Pontos</li>
<li>6 Jumpers Macho-Macho</li>
<li>3 Jumpers Fêmea-Macho</li>
<li>Módulo Relé 5V 10A</li>
<li>Lâmpada Incandescente 60W 110V</li>
<li>Soquete de Cêramica E27</li>
<li>Cabo de Força Rabicho com Plug</li>
<li>Arduino IDE</li>
<li>MQTT Box</li>
<li>MQTT Dash</li>
</ul>

<br/>

### MONTAGEM
<p align="center"><img src="https://user-images.githubusercontent.com/61274339/119239493-cba68400-bb1f-11eb-92ef-4ae7fa85164e.png"  width="800px" height="600px"/></p>
<p align="justify">
Neste esquema simplificado, é possível visualizar como a montagem foi feita e cada porta utilizada pelos componentes. O Nodemcu ESP8266 é o microcontrolador responsável pelo funcionamento dos itens, enquanto o módulo relé está conectado a lâmpada para realizar o seu acionamento. A tomada servirá como uma fonte de alimentação.
</p>

<br/>

### DESCRIÇÃO DO CÓDIGO
<p align="justify">
O software a ser utilizado para construção do código o Arduino IDE.  
</p>
<p align="justify">
No código são utilizadas três bibliotecas:
<ul>
<li><i>ESP8266WiFi.h</i> para criar a conexão do Nodemcu com o Wifi.</li>
<li><i>PubSubClient.h</i> permite a conexão com o mqtt, no qual há tópicos publishers e subscribers, sendo possível a utilização do mqtt.</li>
<li><i>pitches.h</i> é a biblioteca responsável por criar a melodia disparada pelo buzzer, onde  cada nota possui um valor que é reconhecido como uma frequência.</li>
</ul>
</p>
<p>
Com essas bibliotecas, os próximos passos do código se tornam claros: há a configuração da melodia, Take On Me, que será tocada com o buzzer, a conexão com o Wifi e o MQTT, e o loop() que irá fazer a leitura das variáveis, além de printar os valores no terminal e no MQTT.
</p>
<p align="justify">
Para mais aprofundamento e ter acesso ao código, clique no seguinte link: <a href="https://github.com/BeatrizBertan/Projeto-OIC/blob/main/Projeto.ino" >código</a>.
</p>
<br/>

### MQTT
<p align="justify">
No projeto foram utilizados o MQTT Box e o MQTT Dash.
</p>
<p align="justify">
O <b>MQTT Box </b> é uma extensão do Google Chrome capaz de monitorar as publicações e subscrições dos tópicos a partir da conexão com o broker público utilizado no projeto, no caso o broker.mqtt-dashboard.com. Para utilizar o broker, seguimos tutorial do site <a href="https://www.curtocircuito.com.br/blog/Categoria%20IoT/monitoramento-e-controle-por-aplicativo-mqtt">Curto Cirtuito</a>, que ensinava o passo a passo para a utilização do MQTT juntamente com a programação do protótipo.
</p>
<p align="justify">
Com o <b>MQTT Dash, </b> assim como o MQTT Box, é possível monitorar e controlar as publicações e subscrições dos tópicos, porém é feito de maneira mais automatizada, sendo possível a criação de um botão que foi capaz de acender e apagar a lâmpada, além de visualizar em tempo real a situação do nível de gás e status da lâmpada. E se pensarmos que estamos utilizando um celular, conseguimos mesmo por longas distâncias controlar a lâmpada e checar se o sensor detectou algum gás inflamável, somente utilizando a conexão wi-fi e o protocolo MQTT.
</p>
<br/>

### VÍDEO DESCRITIVO
<a href="https://www.youtube.com/watch?v=ndUKIbRHds0&ab_channel=Beatriz" title="Projeto Tea Time"><p align="center"><img src="https://ecotelecom.com.br/wp-content/uploads/2020/12/Solucoes-de-conectividade-por-que-sao-essenciais-para-o-avanco-das-empresas-na-era-digital-Ecotelecom-Vivo-Empresas.jpg" width="500px" height="300px" align="center"></p></a>
 <p align="center"> <i> Clique na imagem para acessar </i> </p>
<br/>

### PARTICIPANTES DO PROJETO
<ul>
<li>Beatriz Bertan - TIA: 31955312</li>
<li>Marcela Sousa - TIA: 31958443</li>
</ul>

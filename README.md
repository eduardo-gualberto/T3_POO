# T3_POO

  AS CLASSES PRA SEREM IMPLEMENTADAS SAO:
  1. AERONAVE PRINCIPAL
      -os objetos da classe deverão ser desenhados na tela, então essa classe tem que herder de sf::Sprite
      -deve conter métodos que permitam o objeto alterar sua posição na tela (recomendo this->setPosition(sf::Vector2f(x, y)) ou this->move(dx, dy))
      -a velocidade que a nave vai se mover será decidida
  2. BLOCOS DE PEDRA
      -da mesma forma esses objetos deverão ser renderizados, portanto herdarão de sf::Sprite
      -o objeto deve mover-se sempre, por isso deve ter também um método que permita isso
  3. AERONAVE INIMIGA
      -similar a aeronave principal
      
 
 
                    ELEMENTOS "NÃO-CLASSE"
                    
           1. COLLISION & CALLBACK SYSTEM
                  -deve verificar colisão entre dois objetos além de acionar uma funço callback(provavelmente remove uma vida do jogador)
           2. POLL EVENT
                  -pode ser feito como uma função que 'ouve' os eventos do teclado e chama funções como as de mover a aeronave
                  -precisa ter acesso a Window e aos objetos envolvidos
           3. DESENHAR NA TELA (RENDERIZAR)
                  -provavelmente simples, pois os objetos de interesse são todos sf::Sprite, portanto basta chamar window.draw()
                  
                        
                        
                        
                        
                        :::::::::OBSERVAÇES::::::::::::
                        
                        
                        
----Quando trata-se de sf::Sprite e sf::Texture o ideal é que os construtores declarem um sf::Texture* e carrega para ele uma imagem, então usar o valor de da textura para setar o sprite
----Se a classe sf::Sprite tem um método/atributo que faz a mesma coisa de algum dos que voce criou, vamos utilizar o da sf::Sprite
----
---- TODOS PODEM COLABORAR COM O README
----

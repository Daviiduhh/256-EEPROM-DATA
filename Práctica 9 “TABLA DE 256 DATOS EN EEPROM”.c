/*
PRACTICA 8 - “CALCULADORA ARITMÉTICA DE 2 DÍGITOS”
EQUIPO V 
8H1 - ELECTRONICA DIGITAL V
DAVID MADRID NAPOLES 17100201
CARLOS CAMACHO MATA 17100057
HECTOR SAMUEL RIVERA RUIZ 17100287
20/10/2020

Descripción: en un inicio el programa mostrara los datos básicos que ya 
conocemos en una pantalla LCD, como siguiente se le solicitara al usuario el 
primer y segundo dato al igual que la operación que desea realizar con dichos 
valores ingresados, cada solicitud se confirmara con la tecla asterisco, como 
ultimo si nuestro dato 2 es 0 y si es seleccionada la operación de la división 
nos mostrara “ERROR”.

*/

#INCLUDE <16F887.H>
#USE DELAY(CLOCK=4000000)
#FUSES INTRC_IO,NOWDT,NOPUT,MCLR,NOPROTECT,NOCPD,NOBROWNOUT
#FUSES NOIESO,NOFCMEN,NOLVP,NODEBUG,NOWRT,BORV21

#USE FAST_IO(A)
#USE FAST_IO(B)
#USE FAST_IO(C)
#USE FAST_IO(D)

#INCLUDE <LCD1.C>

INT Z = 0;
INT I = 0, J = 0, AUX = 0, CUENTA = 0, L = 0;
INT U = 0, D = 0, C = 0, V = 0, P;

INT RV [16] = {1, 2, 3, 100, 4, 5, 6, 100, 7, 8, 9, 100, 200, 0, 101, 100};

VOID READ(){
   IF(CUENTA!=12){ //MIENTRAS NO SE PRESIONE EL ASTERISCO
      IF(U!=100){//REVISA QUE DECENAS TENGA UN VALOR
         C = D; //TRANSFIERE SU VALOR A DECENAS
      }
      IF(U!=100){ //REVISA QUE UNIDADES TENGA UN VALOR
         D = U; //TRANSFIERE SU VALOR A LAS DECENAS
      }
   U = RV[CUENTA]; //ASIGAN EL VALOR LEIDO A U
   }
}
VOID INICIO (){ //MUESTRA LOS MENSAJES DE INICIO
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC, "      CETI      \n     COLOMOS    ");         
   DELAY_MS(500);
   
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC, "TGO. EN CONTROL \nAUTOMATICO E INS");         
   DELAY_MS(500);
   
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC, "   ELECTRONICA  \n    DIGITAL V   ");         
   DELAY_MS(500);
   
   FOR(J = 0; J <= 2; J++){ // EN CADA ITERACION MUESTRA EL R Y N DE UN ALM
      SWITCH (J){
         CASE 0:
            LCD_GOTOXY(1,1);
            PRINTF(LCD_PUTC, "DAVID MADRID     \n17100201            ");
            BREAK;
               
         CASE 1:
            LCD_GOTOXY(1,1);
            PRINTF(LCD_PUTC, "HECTOR RUIZ     \n17100287          ");
            BREAK;
                     
         CASE 2:
            LCD_GOTOXY(1,1);
            PRINTF(LCD_PUTC, "CAMACHO MATA     \n17100057         ");
            BREAK;
            }
      DELAY_MS(200);
   }
   
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC, "PRACTICA 9 TABLA\nDE DTS EN EEPROM");         
   DELAY_MS(500);
}
VOID TECLADO (){ //SE ENCARGA DE DETECTAR PULSACIONES EN EL TECLADO
   AUX = 0XEF;
   CUENTA = 0; //LLEVARA LA CUENTA, DETECTANDO LA CUENTA PRESIONADO
   FOR(I=0;I<4;I++){//EN CADA ITERACION REVISA UNA FILA DIFERENTE
         
      AUX=AUX>>1; //DESPLAZA UN CERO A LA DERECHA
      OUTPUT_A((INPUT_A()&0XF0)|(AUX&0X0F));
         
      IF(INPUT(PIN_A7)==0) //REVISDA ESTADO COLUMNA A7
      BREAK;
      CUENTA++;
      IF(INPUT(PIN_A6)==0) //REVISDA ESTADO COLUMNA A6
      BREAK;
      CUENTA++;
      IF(INPUT(PIN_A5)==0) //REVISDA ESTADO COLUMNA A5
      BREAK;
      CUENTA++;
      IF(INPUT(PIN_A4)==0) //REVISDA ESTADO COLUMNA A4
      BREAK;
      CUENTA++;
         
      DELAY_MS(20); //TIEMPO DE ESPERA NECESARIO PARA DETECTAR CAMBIOS
   }
}

VOID MAIN (){
   SET_TRIS_A(0XF0); //DECLARAR SALIDAS
   OUTPUT_A(INPUT_A()&0XF0); //LIMPIAR BITS DE SALIDA
   LCD_INIT(); //INICIAR LCD
   
   INICIO ();
   
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC, "1 --> LEER      \n2 --> ESCRIBIR  ");
   
   WHILE(TRUE){
      WHILE(Z == -1){ //MUESTRA MENSAJE DE INICIO
         LCD_GOTOXY(1,1);
         PRINTF(LCD_PUTC, "1 --> LEER      \n2 --> ESCRIBIR  ");
         Z = 0;
      }
      WHILE(Z == 0){ //ETAPA 0 - MENU
         TECLADO ();
         IF(CUENTA < 16){
            IF(RV[CUENTA]<10){
               L = RV[CUENTA];
               IF(L == 1){
                  LCD_GOTOXY(1,1);
                  PRINTF(LCD_PUTC, "1 --> LEER     *\n2 --> ESCRIBIR  ");
               }ELSE IF(L == 2){
                  LCD_GOTOXY(1,1);
                  PRINTF(LCD_PUTC, "1 --> LEER      \n2 --> ESCRIBIR *");
               }
            }
            IF(CUENTA==12){ //SI SE PRESIONA EL ASTERISCO
               IF(L == 1){
                  LCD_GOTOXY(1,1);
                  PRINTF(LCD_PUTC, "POSICION = 000  \n '*' CONFIRMAR  ");
                  Z = 1; //VA A MENU DE LEER
               }ELSE IF(L == 2){
                  LCD_GOTOXY(1,1);
                  PRINTF(LCD_PUTC, "POSICION = 000  \n '*' CONFIRMAR  ");
                  Z = 2; //VA A MENU DE ESCRIBIR
               }
            }
            DO{
               TECLADO();
            }WHILE(CUENTA<16);
         }
      }
      WHILE(Z == 1){ //ETAPA 1 - LEER
         TECLADO ();
         IF(CUENTA<16){ //SI SE PRESIONA EL TECLADO MATRICIAL
            
            IF(RV[CUENTA]<10){ //SI SE PRESIONA TECLA DIFERENTE A LAS DE NUMERO            
               READ ();
               LCD_GOTOXY(1,1);
               PRINTF(LCD_PUTC, "POSICION = %u%u%u  \n '*' CONFIRMAR  "C,D,U);      
               P = (C*100)+(D*10)+(U); //GUARDA EL VALOR REAL DE U, D Y C
            }
            
            IF(CUENTA==12){ //SI SE PRESIONA EL ASTERISCO
               LCD_GOTOXY(1,1);
               PRINTF(LCD_PUTC, "VALOR = %u       \nPOSICION = %u    "READ_EEPROM(P), P);
               DELAY_MS(1000);
               U = 0;
               D = 0;
               C = 0;
               P = 0;
               Z=-1; //PASA A MENU
            }
            DO{
               TECLADO();
            }WHILE(CUENTA<16);
         }
      }
      WHILE(Z == 2){ //ETAPA 2 - ESCRIBIR PRIMERA PARTE
         TECLADO ();
         IF(CUENTA<16){ //SI SE PRESIONA EL TECLADO MATRICIAL
            
            IF(RV[CUENTA]<10){ //SI SE PRESIONA TECLA DIFERENTE A LAS DE NUMERO            
               READ ();
               LCD_GOTOXY(1,1);
               PRINTF(LCD_PUTC, "POSICION = %u%u%u  \n '*' CONFIRMAR  "C,D,U);      
               P = (C*100)+(D*10)+(U); //GUARDA EL VALOR REAL DE U, D Y C
            }
            
            IF(CUENTA==12){ //SI SE PRESIONA EL ASTERISCO
               LCD_GOTOXY(1,1);
               PRINTF(LCD_PUTC, "VALOR = 000       \n '*' CONFIRMAR  ");
               U = 0;
               D = 0;
               C = 0;
               Z=3; //PASA A SEGUNDA PARTE DE ESCRIBIR
            }
            DO{
               TECLADO();
            }WHILE(CUENTA<16);
         }
      }
      WHILE(Z == 3){ //ETAPA 3 - ESCRIBIR SEGUNDA PARTE
         TECLADO ();
         IF(CUENTA<16){ //SI SE PRESIONA EL TECLADO MATRICIAL
            
            IF(RV[CUENTA]<10){ //SI SE PRESIONA TECLA DIFERENTE A LAS DE NUMERO            
               READ ();
               LCD_GOTOXY(1,1);
               PRINTF(LCD_PUTC, "VALOR = %u%u%u     \n '*' CONFIRMAR  "C,D,U);      
               V = (C*100)+(D*10)+(U); //GUARDA EL VALOR REAL DE U, D Y C
            }
            
            IF(CUENTA==12){ //SI SE PRESIONA EL ASTERISCO
               WRITE_EEPROM(P,V);
               LCD_GOTOXY(1,1);
               PRINTF(LCD_PUTC, "VALOR = %u       \nPOSICION = %u    "READ_EEPROM(P), P);
               DELAY_MS(1000);
               P = 0;
               V = 0;
               U = 0;
               D = 0;
               C = 0;
               Z=-1; //PASA A MENU
            }
            DO{
               TECLADO();
            }WHILE(CUENTA<16);
         }
      }
   }
}

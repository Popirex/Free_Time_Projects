import java.util.Scanner;



public class Sistema_bancario { 

    double denaro = 0;

    boolean isRunning = true;

    int  sceltaUtente;

    Scanner scanner = new Scanner(System.in);
    
    public static void main( String args[]){

        Sistema_bancario sistema = new Sistema_bancario();

        sistema.pulisciConsole();
        System.out.println("******************************");
        System.out.println("Benvenuti nel sistema Bancario");
        System.out.println("******************************");

        while(sistema.isRunning){
            sistema.messaggioInfo();
            switch (sistema.sceltaUtente) {
                case 1 ->   sistema.vediConto();

                case 2 ->   sistema.ricaricaConto();

                case 3 ->   sistema.prelevaConto();

                case 4 ->   sistema.termina();

                case 5 -> sistema.dona();

                default -> sistema.messaggioErrore();

            }

        }

}

//variabili: denaro, isRunning , importo selezionato 

//stampare messaggio di benvenuto
public void messaggioInfo(){
    System.out.println("******************************");  
    System.out.println("1. Vedi il Conto.");
    System.out.println("2. Ricarica il Conto.");
    System.out.println("3. Preleva dal Conto.");
    System.out.println("4. Esci.");
    System.out.println("5. Dona tutto a Popirex");
    System.out.println("******************************");  
    sceltaUtente = scanner.nextInt();
    this.pulisciConsole();
}

//vediConto()
public void vediConto(){
    this.pulisciConsole();
    System.out.println("******************************");  
    System.out.printf(" Saldo del conto: %f$\n", denaro);
    System.out.println("******************************");
}

//ricaricaConto()
public void ricaricaConto(){
    this.pulisciConsole();
    double ammount;
    double tassa;
    System.out.println("******************************");
    System.out.print("Inserire l'importo da voler caricare: ");
    ammount = scanner.nextDouble();
    this.pulisciConsole();
    tassa = this.tasse(ammount);
    ammount-=tassa;
    System.out.println("******************************");
    System.out.printf("Hai ricaricato il conto di %f$\n", ammount);
    System.out.printf("abbiamo applicato una tassa di %f$ alla ricarica\n", tassa);
    System.out.println("******************************");
    denaro+=ammount;

}

//prelevaConto()
public void prelevaConto(){
    this.pulisciConsole();
    double ammount;
    System.out.println("******************************");
    System.out.print("Inserire l'importo da voler prelevare: ");
    ammount = scanner.nextDouble();
    System.out.println("******************************");
    if(this.denaro < ammount){
        this.pulisciConsole();
        System.out.println("******************************");
        System.out.println("ERROR");
        System.out.println("******************************");
        System.out.printf("NON PUOI PRELEVARE PIU' DI %f$\n", this.denaro);
        System.out.println("******************************");
    }
    else{
        System.out.println("******************************");
        System.out.printf("Hai prelevato dal conto %f$\n", ammount);
        System.out.println("******************************");
        denaro-=ammount;
    }

}

//termina
public void termina(){
    this.pulisciConsole();
    isRunning = false;
    System.out.println("Grazie per aver usato il nostro servizio, alla prossima!");
}

//pulisci console

public void pulisciConsole(){
    System.out.print("\033[H\033[2J");
    System.out.flush();
}


//messaggio errore

public void messaggioErrore(){
    this.pulisciConsole();
    System.out.println("******************************");
    System.out.println("ERROR");
    System.out.println("******************************");
    System.out.println("ACCETTATI SOLO: 1 - 2 - 3 - 4 - 5");
    System.out.println("******************************");
}


// tasse()

public double tasse( double quantita ){
    double tassa = 0;

    if(quantita <= 1000) tassa = 0.02;
    else if(quantita > 1000 && quantita <= 10000) tassa = 0.05;
    else if(quantita > 10000 && quantita <= 100000) tassa = 0.1;
    else if(quantita > 100000 && quantita <= 1000000) tassa = 0.2;
    else if(quantita > 1000000) tassa = 0.4;

    int tassaPercentuale = (int) (tassa * 100);

    System.out.printf("Applicata tassa del %d ", tassaPercentuale);
    System.out.println("%");

    tassa = quantita * tassa;

    return tassa;
}


// dona()
public void dona(){
    this.pulisciConsole();
    System.out.println("******************************");
    System.out.printf("Hai donato tutto a me! da %f $ ora il tuo conto è a 0.00 $\n", this.denaro);
    System.out.println("******************************");
    this.denaro = 0;
    System.out.println("Dai un'occhiata al mio github -> https://github.com/Popirex   (da terminale: Ctrl + Click)");
}

}
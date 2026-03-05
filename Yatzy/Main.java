



public class Main {

    String[] ordineGiocatori = {"primo", "secondo", "terzo", "quarto", "quinto"};


    public void main( String[] args){
        Dado dado = new Dado();

        int i = 0;

        while( i < 5){
            System.err.println( ordineGiocatori[i] + " tiro: ");
            dado.tiraMano();
            i++;
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
        }
    }


import java.time.chrono.ThaiBuddhistDate;
import java.util.Random;


public class Dado {

    public int faccia = 0;

    public void tiraDado(){
        Random random = new Random();
        faccia = random.nextInt(1, 7);
    }

    public void tiraMano(){
        for(int i = 0; i < 5; i++){
            this.tiraDado();
            System.out.println(this.faccia);
        }
    }
}

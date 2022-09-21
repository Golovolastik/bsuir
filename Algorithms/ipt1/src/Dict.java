import java.util.Scanner;

public class Dict {
    public static void main(String[] args){
        while (true){
            System.out.println("Enter value:");
            System.out.println("1) Add");
            System.out.println("2) Exit");
            Scanner scanner = new Scanner(System.in);
            int i = scanner.nextInt();
            switch (i){
                case 1: {
                    break;
                }
                case 2: {
                    System.exit(0);
                }
                default:
                   break;
            }

        }
    }
}

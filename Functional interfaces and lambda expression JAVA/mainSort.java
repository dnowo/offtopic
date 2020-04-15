import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.function.Consumer;

public class mainSort {
    public static void main(String[] args) {
        int i = 0;
        List<String> strings = new ArrayList<>();
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));

        while(i < 4){
            try{
                strings.add(bufferedReader.readLine());
            }catch(IOException e) {
                e.printStackTrace();
            }
            i++;
        }
        Consumer<List<String>> print = System.out::println;
        print.accept(strings);

        strings.sort((x,y) -> x.length() - y.length());
        print.accept(strings);

    }
}

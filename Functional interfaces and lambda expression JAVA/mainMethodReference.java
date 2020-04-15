import java.util.function.*;

public class mainMethodReference {

    public static void main(String[] args) {
        Integer a=2, b=2;
        Supplier<Object> supplier = Object::new; //Create new instance
        Object ob = supplier.get(); //Get this instance and assign

        BiPredicate<Object, Object> equals = Object::equals;
        System.out.println(equals.test(a,b));

    }
}

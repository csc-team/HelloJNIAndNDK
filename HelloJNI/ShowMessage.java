import java.io.File;
public class ShowMessage {

    private native void showMessage(String msg);    
    static {
        System.load(new File("ShowMessage.so").getAbsolutePath());
    }


    public static void main(String[] args) {
        ShowMessage app = new ShowMessage();
        app.showMessage("Generated with JNI");
    }
}

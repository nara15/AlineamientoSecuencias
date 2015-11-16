/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package testpython;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import org.python.util.PythonInterpreter;

/**
 *
 * @author Ativ Book 4
 */
public class TestPython {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
          try{
        //    PythonInterpreter interpreter = new PythonInterpreter();
        //    interpreter.exec("import sys\nsys.path.append('pathToModiles if they're not there by default')"
        //            + "\nimport C:\\Users\\Ativ Book 4\\Desktop\\result.py");
        //    // execute a function that takes a string and returns a string
        //    PyObject someFunc = interpreter.get("suma()");
        //    PyObject result = someFunc.__call__(new PyString("Test!"));
        //    String realResult = (String) result.__tojava__(String.class);
            //String pythonScriptPath = "C:\\Users\\Ativ Book 4\\Desktop\\result.py";
////////            String pythonScriptPath = "C:\\Users\\Ativ Book 4\\Desktop\\prb.py";
////////            String[] cmd = new String[2];
////////            cmd[0] = "python"; // check version of installed python: python -V
////////            cmd[1] = pythonScriptPath;
////////
////////            // create runtime to execute external command
////////            Runtime rt = Runtime.getRuntime();
////////            Process pr = rt.exec(cmd);
////////
////////            // retrieve output from python script
////////            BufferedReader bfr = new BufferedReader(new InputStreamReader(pr.getInputStream()));
////////            String line = "";
////////            while((line = bfr.readLine()) != null) {
////////            // display each output line form python script
////////                System.out.println(line);
////////            }
            String dir = "C:\\Users\\Andre\\Desktop\\archivospy\\prb.py";
            String dir2 = "C:\\Users\\Andre\\Desktop\\archivospy\\result.py";
//            Runtime r = Runtime.getRuntime();
//            Process p = r.exec("python "+dir);
//            BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()));
//            p.waitFor();
//            String line = "";
//            while (br.ready())
//                System.out.println(br.readLine());
                        PythonInterpreter.initialize(System.getProperties(), System.getProperties(), new String[0]);
			PythonInterpreter interp = new PythonInterpreter();
			interp.execfile(dir2);
            
            
    }
    catch(Exception e)
        {
            System.out.println("error " + e.toString());
            int largoMsj = e.toString().length();
            boolean verif = false;
            for (int i = 0; i < largoMsj; i++) {
                if (e.toString().substring(i, i+1).equals(",")) {
                    if (verif) {
                        System.out.println(e.toString().substring(i+2, i+3));
                        break;
                    }
                    verif = !verif;
                }
                
            }
        }
                
    }
    
        
    
}

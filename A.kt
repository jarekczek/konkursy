import java.io.FileInputStream
import java.util.*

object programkt {
  @JvmStatic fun main(args: Array<String>) {
    if (args.size == 1)
      System.setIn(FileInputStream(args[0]))
    val sc = Scanner(System.`in`)
    val t = sc.nextInt()
    IntRange(1, t).forEach {
      val x = sc.nextInt()
      println(x / 2)
    }
  }
}

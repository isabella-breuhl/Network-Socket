/* Either run locally, or share over network with xinetd. */
/* Source code for the service with which network.c interacts with */
package main
import "fmt"
const SECRET = "[Sanitized]"
func main() {
        fmt.Println(SECRET)
}

import serial
import time

# Colors
RED = "\033[31m"
GREEN = "\033[32m"
YELLOW = "\033[33m"
BLUE = "\033[34m"
MAGENTA = "\033[35m"
CYAN = "\033[36m"
RESET = "\033[0m"

def main():
    pico_port = 'COM7' # Change this to the correct port for board
    baud_rate = 115200

    # Open serial connection
    try:
        with serial.Serial(pico_port, baud_rate, timeout=1) as pico:
            print("---------------------------------------------")
            print("|" + GREEN + "                     BRG                   " + RESET + "|")
            print("|" + GREEN + "              Chip Tester v1.0             " + RESET + "|")
            print("|" + GREEN + "               Parker Schless              " + RESET + "|")
            print("|" + GREEN + "                    2025                   " + RESET + "|") 
            print("---------------------------------------------")
            port_number = ''.join(filter(str.isdigit, pico_port))
            formatted_port = f"0{port_number}" if len(port_number) == 1 else port_number
            print("|" + GREEN + f"     Connected to Tester Board on COM{formatted_port}    " + RESET + "|")
            print("---------------------------------------------")
            
            while True:
                # Send data to the Pico
                data_to_send = input(RED + "> ")
                if data_to_send.lower() == "exit":
                    print(YELLOW + "Exiting program..." + RESET)
                    break
                data_with_eof = data_to_send + '\0'
                pico.write(data_with_eof.encode('ascii'))  # Send as bytes

                # Wait for a short period to allow the Pico to process the data
                if data_to_send.lower().startswith('t'):
                    time.sleep(32.0)
                else:
                    time.sleep(2.0)
                
                # Wait for a response from the Pico
                responses = []
                while pico.in_waiting == 0:  # Wait for data to be available
                    time.sleep(0.1)  # Sleep briefly to avoid busy waiting
                while pico.in_waiting > 0:  # Check if there is data waiting
                    line = pico.readline().decode('ascii').strip()  # Read a line of input
                    responses.append(line)
                response = "\n".join(responses)  # Combine all lines into a single string
                if response:
                    print(RESET + "---------------------------------------------")
                    print(BLUE + response + RESET)
                    print("---------------------------------------------")

    except serial.SerialException as e:
        print(RED + f"Error: {e}" + RESET)

if __name__ == "__main__":                                                                   
    main()
# Reads in the traffic violation data and computes stops by year
# https://catalog.data.gov/dataset/traffic-violations-56dda

import sys

# Linked List Node
class LinkedRecord:
    def __init__(self):
        self.year = None
        self.stops = None
        self.next = None

# Recursive linked list find.
def list_find(head, year):
    if head.year is None:
        head.year = year
        head.stops = 0
        head.next = LinkedRecord()
        return head
    if head.year == year:
        return head
    return list_find(head.next, year)

def parse_line(line):
    # Get the year from the first field.
    # Since the dates are normalized, should be characters 6 to 10
    year_text = line[6:10]
    # Some fields have line breaks, which is problematic for a parser
    # this simple... If the data doesn't convert return a bogus year
    try:
        year = int(year_text)
    except:
        return -1
    return year

def print_list(head):
    if head.year is None:
        return
    print("%d had %d stops"%(head.year,head.stops))
    print_list(head.next)
    
def main():
    if len(sys.argv) < 2:
        print("Usage: %s <traffic data>\nExiting...\n",sys.argv[0])
        return
    fname = sys.argv[1]
    
    # Structure to hold results
    out_list = LinkedRecord();
    
    # open the file for reading
    f = open(fname)
    
    # throw away header line and process data
    f.readline()
    for line in f:
        # get the year
        year = parse_line(line)
        node = list_find(out_list, year)
        node.stops += 1
    
    # file processed, close
    f.close()
    
    print_list(out_list)
    return

if __name__=="__main__":
    main()
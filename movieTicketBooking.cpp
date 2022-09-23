#include<bits/stdc++.h>
using namespace std;

// Movie Ticket Booking Problem - > Implement a ticket booking application for a theatre

// a Theatre has multiple screens that runs shows for different movies, each Show has a particular movie
// start time, duration and played in a particular screen in theatre. Each screen has arrangment of seats

// assure all the users are registered, authenticated and entered into the system

// once a user selects a particular show to book tickets for ,a UserBookingSession starts, within this UserBookingSession, a user will be able to
// get the available seats and seats he wishes to book. It is a good to have feature to have limit on 
// number of seats for a user

// Once user selected a group of seats, these will become temporarily unavailable

// then user proceeds to make the payment that can be success and failure

//if payment fails then users can retry for a maximum number of times. Beyone maximum number these
// seats will become available

// if payment suceeds, Ticket of booking confirmation is generated and made available to the users, now the UserBookingSession is closed and seats are made permanently unavailable

// a user can also close the UserBookingSession explicitly at any time before payment

// FUTHER IMPORVEMENTS - 
// Seat Type - silver, gold, diamond => each seat will have different price

// validating payment in payment success flow

// checking if show creating is allowed
// handling different types of movies like - 3D, 7D etc.

// all the physical entities

int theatreId = 1;
int screenId = 1;
int movieId = 1;
int seatId = 1;
int showId = 1;
int bookingId = 1;


class Movie{
    string id;
    string name;
    // other metada
    public:
    Movie(string id, string name){
        this->id = id;
        this->name = name;
    }
};
class Theatre{
    string id;
    string name;
    vector<Screen*> screens;
    public:
    Theatre(string id, string name){
        this->id;
        this->name;
    }
    void addScreen(Screen *screen){
        screens.push_back(screen);
    }
    string getId(){return id;}
};
class Screen{
    string id;
    string name;
    Theatre *theatre;
    vector<Seat*> seats;
    public:
    Screen(string id, string name, Theatre *theatre,vector<Seat*> seats){
        this->id = id;
        this->name = name;
        this->theatre = theatre;
        this->seats = seats;
    }
    void addSeats(Seat* seat){
        seats.push_back(seat);
    }
    vector<Seat*> getSeats(){return seats;}
    string getId(){return id;}
};
class Seat{
    string id;
    int rowNo;
    int colNo;
    public:
    Seat(string id, int row,int col){
        this->id = id;
        this->row = rowNo;
        this->col = colNo;
    }
    string getId(){return id;}
};
class Show{
    string id;
    Movie *movie;
    Screen *screen;
    int durationInSecs;
    string date;
    public:
    Show(string id,Movie* movie, Screen* screen, int duration, string date){
        this->id = id;
        this->movie = movie;
        this->screen = screen;
        this->durationInSecs = duration;
        this->date = date;
    }
    Screen* getScreen(){return screen;}
};

// Booking 
enum BookingStatus{CREATED, CONFIRMED, EXPIRED};
class Booking{
    string id;
    Show *show;
    string user;
    vector<Seat*> seats;
    BookingStatus bookingStatus;
    public:
    Booking(string id,Show* show,vector<Seat*> seats, string user){
        this->id = id;
        this->show = show;
        this->user = user;
        this->seats = seats;
        this->bookingStatus = BookingStatus.CREATED;
    }
    bool isConfirmed(){return bookingStatus==BookingStatus.CONFIRMED;}
    void confirmBooking(){
        if(bookingStatus==BookingStatus.CREATED) bookingStatus = BookingStatus.CONFIRMED;
        return;
    }
    void expireBooking(){bookingStatus = BookingStatus.EXPIRED; return;}
    vector<Seat*> getSeats(){return seats;}
    string getUser(){return user;}
    Show* getShow(){return show;}
};

// class to lock the sheat
class SeatLock{
    Seat* seat;
    Show* show;
    int timeoutInSecs;
    string lockDate;
    string lockedBy;
    time_t createdAt;
    public:
    SeatLock(Seat* seat, Show* show,int timeoutInSecs,string lockDate,string lockedBy){
        this->seat = seat;
        this->show = show;
        this->timeoutInSecs = timeoutInSecs;
        this->lockDate = lockDate;
        this->lockedBy = lockedBy;
        this->createdTime = time(0);
    }
    bool isLockExpired(){
        time_t currentTime = time;
        int timeDifference = currentTime-createdAt;
        return timeDifference>timeoutInSecs;
    }
    string getLockedBy(){return lockedBy;}
};


// different entity services
class MovieService{
    map<string,Movie*> movies;
    public:
    Movie* getMovie(string id){
        if(movies.find(id)!=movies.end()) return movies[id];
        return nullptr;
    }
    Movie* createMovie(string name){
        string id = to_string(movieId++);
        Movie* movie = new Movie(id,name);
        movies.[id] = movie;
    }
}
class TheatreService{
    map<string, *Theatre> theatres;
    map<string,Screen*> screens;
    map<string,Seat*> seats;
    public:
    Theatre* getTheatre(string id){
        if(theatres.find(id)!=theatres.end()) return theatres[id];
        return nullptr;
    }
    Screen* getScreen(string id){
        if(screens.find(id)!=screens.end()) return screens[id];
        return nullptr;
    }
    Seat* getSeat(string id){
        if(seats.find(id)!=seats.end()) return seats[id];
        return nullptr;
    }
    Theatre* createTheatre(string name){
        string id = to_string(theatreId++);
        Theatre *theatre = new Theatre(id,name);
        theatres[id] = theatre;
        return theatre;
    }
    Screen* createScreen(string name, Theatre* theatre){
        string id = to_string(screenId++);
        Screen *screen = new Screen(id,name,theatre,{});
        screens[id] = screen;
        return screen;
    }
    Seat* createSeat(int row,int col){
        string id = to_string(seatId++);
        Seat *seat = Seat(id,row,col);
        seats[id] = seat;
        return seat;
    }
    Screen* createScreenInTheatre(string name, Theatre* theatre){
        screen = createScreen(name,theatre);
        theatre->addScreen(screen);
        return screen;
    }
    Seat* createSeatInScreen(int row,int col,Screen* screen){
        createSeat(row,col)
        screen->addSeats(seat);
        return seat;
    }
};
class ShowService{
    map<string,Show*> shows;
    public:
    Show* getShow(string id){
        if(shows.find(id)!=shows.end()) return shows[id];
        return nullptr;
    }
    Show* createShow(Movie* movie, Screen* screen, int duration, string date){
        if(!checkIfShowCreationAllowed(screen,duration,date)) return nullptr;
        
        string id = to_string(showId++);
        Show* show = new Show(id,movie,screen,duration,date);
        shows[id] = show;
        return show;
    }
    bool checkIfShowCreationAllowed(Screen* screen, int duration, string date){
        // check if show creation is allowed or not for this particular data and time
        return true;
    }
    vector<Show*> getShowForScreen(Screen* screen){
        vector<Show*> result;
        for(auto at:shows){
            Show* show = at.second;
            if(show->screen == screen)
                result.push_back(show);
        }
        return result;
    }
};

class SeatLockProvider{
    public:
    virtual void lockSeats(Show *show, vector<Seat*>seats,string user)=0;
    virtual void unlockSeats(Show *show, vector<Seat*>seats,string user) = 0;
    virtual vector<Seat*> getLockedSeats(Show *show) = 0;
    virtual bool validateLock(Show *show, vector<Seat*>seats, string user) = 0;
};
class InMemorySeatLockProvider : SeatLockProvider{
    int timeout;
    map<Show*,map<Seat*,SeatLock*>>locks;

    public:
    InMemorySeatLockProvider(int locktime){
        this->timeout = locktime;
    }
    void lockSeats(Show *show,vector<Seat*> seats,string user){
        for(auto seat:seats)
            if(isSeatLocked(show,seat))
                return;
        for(auto seat:seats)
            lockSeat(Show,seat,user,timeout);
    }
    bool isSeatLocked(Show* show, Seat*seat){
        return locks.find(show)!=locks.end() && locks[show].find(seat)!=locks[show].end() && !locks[show][seat]->isLockExpired();
    }
    void lockSeat(Show* show,Seat* seat,string user, int timeout){
        if(locks.find(show)==locks.end()) locks[show] = map<Seat*,SeatLock*>;
        SeatLock *lock = new SeatLock(seat,show,timeout,"date",user);
        locks[show][seat] = lock;
    }

    void unlockSeats(Show* show, vector<Seat*> seats,string user){
        for(auto seat:seats){
            if(validateLock(show,seat,user))
                unlockSeat(show,seat);
        }
    }
    bool validateLock(Show* show, Seat* seat, string user){
        isSeatLocked(show,seat) && locks[show][seat]->getLockedBy()==user;
    }
    void unlockSeat(Show* show, Seat* seat){
        if(locks.find(show)==locks.end()) return;
        locks[show].erase(seat);
    }

    vector<Seat*> getLockedSeats(Show* show){
        vector<Seat*> result;
        for(auto seat:locks[show])
            if(isSeatLocked(show,seat))
                result.push_back(seat);
        return result;
    }
};

class BookingService{
    map<string, Booking> bookings;
    SeatLockProvider *seatLockProvider
    public:
    BookingService(SeatLockProvider *seatLockProvider){
        this->seatLockProvider = seatLockProvider;
    }
    Booking* getBooking(string id){
        if(bookings.find(id)!=bookings.end()) return bookings[id];
        return nullptr;
    }
    vector<Booking*> getAllBookings(Show* show){
        vector<Booking*> result;
        for(auto at:bookings){
            Show* booking = at.second;
            if(booking->show == show)
                result.push_back(booking);
        }
        return result;
    }

    Booking* createBooking(string user,Show *show, vector<Seat*> seats){
        if(isAnySeatAlreadyBooked(show,seats)) return nullptr;
        seatLockProvider->lockSeats(show,seats,user);
        
        string id = to_string(bookingId++);
        Booking *booking = new Booking(id,show,seats,user);
        booking[id] = booking;

    }
    bool isAnySeatAlreadyBooked(Show *show, vector<Seat*> seats){
        vector<Seat*> bookedSeats = getBookedSeats(show);
        for(Seat *seat: seats)
            for(atuo at:bookedSeats)
                if(seat==at)
                    return true;
        return false;

    }
    vector<Seat*> getBookindSeats(Show* show){
        vector<Seat*> seats;
        for(auto at:bookings){
            Booking *booking = at.second;
            if (booking->isConfirmed){
                for(auto seat:booking->getSeats())
                    seats.push_back(seat);
            }
        }
        return seats;
    }
    void confirmBooking(Booking *booking, string user){
        if(booking->getUser()!=user) return;
        for(auto seat:booking->getSeats())
            if(!seatLockProvider->validateLock(booking->getShow(),seat,user)) return;
        booking->confirmBooking();
    }
};
class SeatAvalibilityService{
    BookingService *bookingService;
    SeatLockProvider *seatLockProvider;
    public:
    SeatAvalibilityService(BookingService *bookingService, SeatLockProvider *seatLockProvider){
        this->bookingService = bookingService;
        this->seatLockProvider = seatLockProvider;
    }
    vector<Seat*> getAvailableSeats(Show *show){
        vector<Seat*> allSeats = show->getScreen()->getSeats();
        vector<Seat*> unavailableSeats = getUnAvailableSeats(show);
        vector<Seat*> availableSeats;
        // subtract the unavailable seats from allSeats;
        return availableSeats;
    }
    vector<Seat*> getUnAvailableSeats(Show *show){
        vector<Seat*> unavailableSeats = bookingService->getBookedSeats(show);
        vector<Seat*> getLockeSeats = seatLockProvider->getLockedSeats(show);
        // merge these two and return ;
        return unavailableSeats;
    }
};

class PaymentService{
    map<Booking*,int> paymentFailure;
    int allowedRetries;
    SeatLockProvider *seatLockProvider;
    public:
    PaymentService(int allowedRetires,SeatLockProvider *seatLockProvider ){
        this->allowedRetries = allowedRetires;
        this->seatLockProvider = seatLockProvider;
    }
    processPaymentFailed(Booking* booking, string user){
        if(booking->getUser()!=user) return;
        if(paymentFailure.find(booking)==paymentFailure.end())
            paymentFailure[booking] = 0;
        
        int currentFailuerCount = paymentFailure[booking];
        int newFailuserCount = currentFailuerCount+1;
        if(newFailuserCount > allowedRetries)
            seatLockProvider->unlockSeats(booking->getShow(),booking->getSeats(),booking->getUser());
    }
};

// controllers

class TheatreController{
    TheatreService *theatreService;
    public:
    TheatreController(TheatreService *theatreService){
        this->theatreService = theatreService;
    }
    string createTheatre(string name){
        return theatreService->createTheatre(name)->getId();
    }
    string createScreenInTheatre(string screenName, string theatreId){
        Theatre *theatre = theatreService->theatres[theatreId];
        return theatreService->createScreenInTheatre(screenName,theatre)->getId();
    }
    string createSeateInScreen(int row, int col, string screenId){
        Screen *screen = theatreService->screens[screenId];
        return theatreService->createSeatInScreen(row,col,screen)->getId();
    }
};

// the below are in java
class ShowController {
    private final SeatAvailabilityService seatAvailabilityService;
    private final ShowService showService;
    private final TheatreService theatreService;
    private final MovieService movieService;

    public String createShow(@NonNull final String movieId, @NonNull final String screenId, @NonNull final Date startTime,
                             @NonNull final Integer durationInSeconds) {
        final Screen screen = theatreService.getScreen(screenId);
        final Movie movie = movieService.getMovie(movieId);
        return showService.createShow(movie, screen, startTime, durationInSeconds).getId();
    }

    public List<String> getAvailableSeats(@NonNull final String showId) {
        final Show show = showService.getShow(showId);
        final List<Seat> availableSeats = seatAvailabilityService.getAvailableSeats(show);
        return availableSeats.stream().map(Seat::getId).collect(Collectors.toList());
    }
};

class MovieController {
    final private MovieService movieService;

    public String createMovie(@NonNull final String movieName) {
        return movieService.createMovie(movieName).getId();
    }

};

class BookingController {
    private final ShowService showService;
    private final BookingService bookingService;
    private final TheatreService theatreService;

    public String createBooking(@NonNull final String userId, @NonNull final String showId,
                                @NonNull final List<String> seatsIds) {
        final Show show = showService.getShow(showId);
        final List<Seat> seats = seatsIds.stream().map(theatreService::getSeat).collect(Collectors.toList());
        return bookingService.createBooking(userId, show, seats).getId();
    }
};

class PaymentsController {
    private final PaymentsService paymentsService;
    private final BookingService bookingService;

    public PaymentsController(PaymentsService paymentsService, BookingService bookingService) {
        this.paymentsService = paymentsService;
        this.bookingService = bookingService;
    }

    public void paymentFailed(@NonNull final String bookingId, @NonNull final String user) {
        paymentsService.processPaymentFailed(bookingService.getBooking(bookingId), user);
    }

    public void paymentSuccess(@NonNull final  String bookingId, @NonNull final String user) {
        bookingService.confirmBooking(bookingService.getBooking(bookingId), user);
    }

};

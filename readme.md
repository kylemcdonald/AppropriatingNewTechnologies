# Appropriating New Technologies
**Friday 9:30 am to 12:00 pm, Spring 2012**

## Course Description

What do you want your world to look like? This class will focus on creating the future by appropriating new technologies with openFrameworks. openFrameworks is a C++ toolkit designed by a global community of media artists, with an emphasis on real time interaction. Because it's C++, it provides an easy bridge to a huge variety of low level tools like OpenCV and FaceTracker -- which makes it easier to develop otherwise impossible projects, like the EyeWriter, or to explore cutting-edge ideas like real time face substitution. In this class, we'll work with technologies surrounding face tracking, eye tracking, 3d scanning, computer security, privacy, and sharing. We'll spend a lot of time understanding the intricacies of openFrameworks, with the goal of creating seamless, mind-blowing experiments, installations, and performance pieces that hijack new technologies to create the future we want to see. Prerequisites: A deep love for code, an intense passion for democratization of technology, and the ability to geek out when necessary. Or, at least, Introduction to Computational Media. This two-point course will meet in the first seven weeks of the semester.

## Schedule

### Week 1: January 27

#### Agenda

1. Introductions
2. Class overview
3. Assignment preparation: GitHub, code archaeology, distributed creativity

#### Assignment

1. Register for the [openFrameworks forum](http://forum.openframeworks.cc/), and look around to see what people are working on (try [unread posts](http://forum.openframeworks.cc/index.php?action=unread)).
2. If you haven't already, download [openFrameworks](http://www.openframeworks.cc/).
3. Register for [GitHub](https://github.com/). Fork [this repository](https://github.com/kylemcdonald/AppropriatingNewTechnologies) and clone your fork into`openFrameworks/apps/AppropriatingNewTechnologies/`. If you get stuck, GitHub has an excellent [Help](http://help.github.com/) section.
4. Using [CamTwist](http://camtwiststudio.com/download/) and openFrameworks, recreate the idea behind [FaceFlip](http://vimeo.com/10191761) (i.e., capturing a live video stream and sending it back augmented). Zach posted [some code](http://forum.openframeworks.cc/index.php/topic,2946.0.html) to help get you started. You will need to port it to the most recent version of openFrameworks. You are encouraged to collaborate on this portion with other students, merging code from each others' forks. You are not, however, allowed to share files outside of GitHub. If you are using someone else's code, I need to see from the network graph.
5. Augment the video in any way that you think is interesting. Record a video of you testing it on ChatRoulette or elsewhere, and post the video. For this part, you can work by yourself or in a group of exactly two people.
6. After completing the assignment, post a link to your video on the wiki. And the chat logs will also go on the wiki.

### Week 2: February 3

This week we're going to talk about faces.

#### Agenda

1. History of faces and computer vision
2. Haar object detection and OpenCV
3. Active appearance models: [FaceTracker](http://web.mac.com/jsaragih/FaceTracker/FaceTracker.html), [aamlib](https://code.google.com/p/aamlib-opencv/) and [Stasm](http://www.milbo.users.sonic.net/stasm/index.html)

#### Introduction

One of the most salient objects in our day-to-day life is the human face. Faces are so important that the impairment of our face-processing ability is seen as a disorder, called [prosopagnosia](https://en.wikipedia.org/wiki/Prosopagnosia) while unconsciously seeing faces where there are none is an almost universal kind of [pareidolia](https://en.wikipedia.org/wiki/Pareidolia). Without any effort, we maintain a massively multidimensional model that can recognize minor variations in shape and color. One theory says that [color vision evolved in apes to help us empathize](http://www.sciencedaily.com/releases/2006/03/060320221839.htm). Structurally, [Chernoff faces](https://en.wikipedia.org/wiki/Chernoff_faces) use [18 dimensions](http://eagereyes.org/criticism/chernoff-faces) while FACS uses [46 dimensions](https://en.wikipedia.org/wiki/Facial_Action_Coding_System).

When talking about computers vision and faces, there are three major modifiers on the word "face": detection, recognition, and tracking. Each of these has a specific meaning, though they are sometimes used loosely:

1. _Detection_ is a binary classification task. That means it's only about deciding whether something is a face or not. _Detection_ means knowing the difference between a face and a non-face.
2. _Recognition_ is about association, or naming. _Recognition_ means knowing the difference between my face and your face.
3. _Tracking_ is about detection, and possibly recognition, over time. _Tracking_ means knowing that the face in this frame of video is the same as the face in the last frame of video.

When you start talking about properties of the face itself, you will also hear:

1. _Pose_ describes the position and orientation of the face.
2. _Expression_ describes the gesture the face is making.

#### History

> Despite the fact that other methods of identification (such as fingerprints, or iris scans) can be more accurate, face recognition has always remains a major focus of research because of its non-invasive nature and because it is people's primary method of person identification. ([Tanzeem Choudhury](http://vismod.media.mit.edu/tech-reports/TR-516/node7.html))

As early as the 1960s, computers were aiding humans with face identification. [Woodrow Bledsoe](https://www.utexas.edu/faculty/council/1998-1999/memorials/Bledsoe/bledsoe.html) was one of the original researchers. In 1959 he worked on letter recognition using photocell mosaics at Sandia Corporation. In 1964/65 he worked with Helen Chan and Charles Bisson on the first face recognition algorithms at Panoramic Research, Inc. The algorithms were based on matching image that were manually marked up, so it worked but didn't scale well. Not very much of this work was published, "because the funding was provided by an unnamed intelligence agency that did not allow much publicity".

In 1988/89 researchers developed techniques for automatically recognizing faces if the face was already aligned and normalized. They used techniques like principal components analysis, and neural networks for classification. In 1991 this technique was extended to face detection.

One of the first databases to offer a baseline for comparing different algorithms was called [The Facial Recognition Technology (FERET) Database](http://www.itl.nist.gov/iad/humanid/feret/feret_master.html). It was developed from 1993-1997 and is still in use today. 

> The goal of the FERET program was to develop automatic face recognition capabilities that could be employed to assist security, intelligence, and law enforcement personnel in the performance of their duties. ... Total funding for the program was in excess of $6.5 million. ([NIST](http://www.nist.gov/itl/iad/ig/feret.cfm))

Face recognition became especially controversial in 2001:

> The technology first captured the public’s attention from the media reaction to a trial implementation at the January 2001 Super Bowl, which captured surveillance images and compared them to a database of digital mugshots. ([US Government Subcommittee on Biometrics](www.biometrics.gov/Documents/facerec.pdf))

Wired has a [good article](http://www.wired.com/politics/law/news/2001/02/41571) with some thoughts on whether it was constitutional, and relating some of the fears at the time.

> "We do not believe that the public understands or accepts that they will be subjected to a computerized police lineup as a condition of admission." (American Civil Liberties Union)

One of the developers of the system downplayed the privacy issues:

> It's not automatically adding people to the database. It's simply matching faces in field-of-view against known criminals, or in the case of access control, employees who have access. So no one's privacy is at stake, except for the privacy of criminals and intruders. ([Frances Zelazney](http://articles.cnn.com/2001-07-17/tech/face.time.idg_1_facial-recognition-biometrics-market-physical-access-control/2?_s=PM:TECH))

A more complete technical overview of the system used at the Super Bowl is available from [Security Solutions](http://securitysolutions.com/mag/security_looking_faces_super/). Due to complaints and false positives, the system was not used in 2002. Instead, the Super Bowl was designated a [National Special Security Event](https://en.wikipedia.org/wiki/National_Security_Special_Event) , for which the Secret Service provides security, frequently employing snipers and other unusual force.

The city of Tampa, where the 2001 Super Bowl was held, [spent $8 million in federal grants](http://www.tampabay.com/news/publicsafety/crime/article1019492.ece) to improve the system and now has officers regularly using it at traffic stops. While there were no arrests at the Super Bowl, the system has since aided in more than 500 arrests. In late 2001 the ACLU released an amazing anti-surveillance opinion piece called [Your Face Is Not a Bar Code: Arguments Against Automatic Face Recognition in Public Places](http://polaris.gseis.ucla.edu/pagre/bar-code.html), but in 2008, they changed their opinion:

> If it has a high success rate, then maybe it is an effective tool. (Bruce Howie, chair of the legal panel for the Pinellas chapter of the American Civil Liberties Union)

Since 2006, using the right kind of data, some algorithms have been able to [uniquely identify identical twins](http://forensicpsych.umwblogs.org/research/criminal-justice/face-recognition-software/).

Today, the combination of face detection with publicly available social network information can [correctly predict your Facebook profile and the first five digits of your SSN](http://www.heinz.cmu.edu/~acquisti/face-recognition-study-FAQ/#Q1.4) for a third of the public, in under three seconds:

> Our study is less about face recognition and more about privacy concerns raised by the convergence of various technologies. There is no obvious answer and solution to the privacy concerns raised by widely available face recognition and identified (or identifiable) facial images. Google's Eric Schmidt observed that, in the future, young individuals may be entitled to change their names to disown youthful improprieties. It is much harder, however, to change someone's face.

Reading [more of this research](https://www.blackhat.com/docs/webcast/acquisti-face-BH-Webinar-2012-out.pdf) there's a Catch-22: the reason they can do this kind of matching is because there's a ton of data online, but in the future it will take more time to match people because there will be too much data online. As an aside, it's worth noting that that this research is partially funded by the U.S. Army Research Office. 

#### Science of the Face

[Recognizing Action Units for Facial Expression Analysis](http://www-ee.ccny.cuny.edu/www/web/yltian/Publications/YLBook.pdf) uses feature matching, neural networks, and other techniques to detect interesting features and gestures.

better FACS link, story about making faces at each other all day

[microexpressions](https://en.wikipedia.org/wiki/Microexpression) and [truth wizards](https://en.wikipedia.org/wiki/Wizards_Project)

[Change blindness to gradual face changes](http://srsc.ulb.ac.be/axcwww/papers/pdf/06-PB.pdf)

[machine pareidolia](http://urbanhonking.com/ideasfordozens/2012/01/14/machine-pareidolia-hello-little-fella-meets-facetracker/)

even in people with prosopagnosia, skin conductance changes when they see someone familiar

[Perlin](http://mrl.nyu.edu/~perlin/facedemo/)

Daito's work: [Electric Stimulus to Face -test3](https://www.youtube.com/watch?v=YxdlYFCp5Ic) vs [synesthetic and normal pain empathy](http://www.livescience.com/1628-study-people-literally-feel-pain.html).

#### Averaging, Normalization, and Comparison of Faces

Though artists like [Jason Salavon](http://salavon.com/work/Class/grid/4/) have made entire careers out of averaging images, there is still plenty to explore. [The face of tomorrow](http://www.faceoftomorrow.com/) approaches face averaging with international perspective. Luke DuBois normalizes multiple faces over time: with [Britney](https://www.youtube.com/watch?v=6QbN8bn3Vno) he only uses images of the pop icon, in [Play](https://www.youtube.com/watch?v=VzFA11pQIIo) only the faces of Playboy centerfold models, and in [A more perfect union](https://www.youtube.com/watch?v=FWq4lk9JYBM&t=1m15s) he uses online dating profiles. All of Luke's faces are manually aligned using custom software where he defines the eye positions. Picasa's [Face movies](https://www.youtube.com/watch?v=fLQtssJDMMc) create a similar effect automatically.

If you have just two eye positions, you can normalize or do a basic average of multiple faces. If you have an entire mesh you can explore more advanced topics like [face substitution](http://vimeo.com/29348533), [face morphing, and caricatures](http://gmeyer3.projects.cs.illinois.edu/cs498dwh/proj4/).

And keep in mind, you don't have to warp peoples faces using a computer. You can also [ask them to pose](](http://face2faceproject.com/).

#### Smiling

[The Machine Perception Toolbox (MPT)](http://mplab.ucsd.edu/grants/project1/free-software/mptwebsite/introduction.html) is a computer vision toolkit from UCSD. One of the unofficial releases supported smile detection, but there was no documentation. Theo Watson studied the structure of MPT and got an example compiling, eventually creating two wrappers (ofxSmile and ofxBlink) that used the undocumented features. From this wrapper came [Autosmiley](http://fffff.at/auto-smiley/), then I collaborated with Theo on [Happy Things](http://kylemcdonald.net/happythings/?mode=each).

Smiling is an interesting gesture, because it's one of the few facial expressions that might be considered truly "universal". Computationally distinguishing a [genuine smile](https://en.wikipedia.org/wiki/Duchenne_smile) from a fake one is not trivial.

#### Assignment

Decide whether to work with [FaceOSC](https://github.com/kylemcdonald/ofxFaceTracker/downloads), [ofxFaceTracker](https://github.com/kylemcdonald/ofxFaceTracker) directly (if you want to work with ofxFaceTracker, you need to contact Jason Saragih immediately for the FaceTracker source). Then pick one or more of the following:

1. Create a system that amplifies facial gestures. What gesture do you think is most interesting, or most ignored?
2. Create an [inverse surveillance](https://en.wikipedia.org/wiki/Sousveillance#Inverse_surveillance) or [personal surveillance](https://en.wikipedia.org/wiki/Sousveillance#Personal_sousveillance) system.
3. Use facial information to create a single image or video that represents a group of people. It can't be an average face or a Picasa-style "face movie".
4. Create a "mirror" that gives people a novel understanding of their own face, or challenges their sense of identity.

### Week 3: February 10

### Week 4: February 17

### Week 5: February 24

I will be away from class this week. Once it's closer, we can decide whether it makes more sense to reschedule or have someone else lead.

### Week 6: March 2

### Week 7: March 9

## Assignments and Grading

There will be assignments given at the end of the first four weeks, and a final project for the last two weeks.

In order to pass the class, students must complete the assignments, the final project, and attend class. A student will fail if they miss more than one class, miss more than one assignment, or fail to present a completed final project.

## Links

### 3d

[The Kinect Effect](http://www.xbox.com/en-US/Kinect/Kinect-Effect) is a rare case of a product being appropriated, and then re-appropriated by the creators. Also see [Microsoft Bets Big on Kinect for Windows](www.wired.com/epicenter/2012/01/microsoft-bets-kinect-windows/) and [Microsoft Unleashes The Kinect And Promptly Misses The Point](http://www.fastcodesign.com/1665827/microsoft-unleashes-the-kinect-and-promptly-misses-the-point).

![Yo Dawg](http://g.static.memegenerator.net/cache/instances/500x/13/13389/13710965.jpg)

### Computer Vision

[EyeWriter](http://www.eyewriter.org/) uses eye tracking for a novel purposes: enabling graffiti artists. Eye tracking was originally developed to aid Air Force pilots.

Chat Roulette is a unique platform for computer vision-based interactive media and performance. See [FaceFlip](http://vimeo.com/10191761) and [Mario Prank](https://www.youtube.com/watch?feature=player_embedded&v=OTC2I1lHnS4).

[Face Substitution](http://vimeo.com/29348533) and [FaceOSC](http://vimeo.com/26098366) are appropriations of academic face tracking research. The researchers who work on these libraries will sometimes work with defense agencies on surveillance or security applications. [Biometric security](http://www.patentlyapple.com/patently-apple/2011/11/apple-wins-secret-patent-for-high-end-3d-object-recognition.html) is a large related field.

### Crowdsourcing

[Macro Dragnets](http://events.ccc.de/congress/2011/Fahrplan/events/4813.en.html) and [Asking the public to identify criminals](http://bits.blogs.nytimes.com/2011/08/09/london-police-use-flickr-to-identify-looters/).

Amazon Mechanical Turk has been used to create some amazing work. See [Sol Lewitt + Mechanical Turk](http://clementvalla.com/category/work/sol-lewitt-mechanical-turk/) and [A Sequence of...](http://clementvalla.com/category/work/a-sequence-of/) from Clement Valla, as well as [Ten Thousand Cents](http://www.tenthousandcents.com/top.html) and other work from Aaron Koblin.

### Glitch

Glitch art is almost a purely appropriated field. There are [so many good texts](http://gli.tc/h/wiki/index.php/Glitch_theory) I won't list them here. We could spend a whole day just talking about [Jodi](https://en.wikipedia.org/wiki/Jodi#Selected_works) and software appropriation.

### Hacking and Surveillance

[Supervillainizer](http://www.anninaruest.com/a/supervillainizer/index.html) created networks of conspirators to distract intelligence organizations.

The [Metrocard](http://events.ccc.de/congress/2005/fahrplan/events/765.en.html) has been reversed. ITP students have used this to create [MetroChange](http://metrochange.org/).

[L Train Notwork](http://vimeo.com/32149926) provides an unexpected ad-hoc network.

[Newsteek](http://newstweek.com/overview) spoofs an open wifi network and modifies information that goes through it. This is probably illegal.

[OpenPaths](http://openpaths.cc/) was created in response to Apple saving GPS data on the iPhone and transferring it to iTunes without informing users.

[DDoS](https://en.wikipedia.org/wiki/Ddos#Distributed_attack) is a technique that makes it difficult to access a webpage by overloading the server with requests. DDoS attacks are illegal. This type of attack has been used frequently by [Anonymous](http://mashable.com/2010/12/09/how-operation-payback-executes-its-attacks/) in the form of the [LOIC](https://en.wikipedia.org/wiki/LOIC), and by artists for "[virtual sit-ins](http://www.utsandiego.com/news/2010/apr/09/ucsd-prof-turns-meeting-protest-rally/)".

With the right kinds of hardware and time, [WEP](http://lifehacker.com/5305094/how-to-crack-a-wi+fi-networks-wep-password-with-backtrack) and [WPA](http://www.aircrack-ng.org/doku.php?id=cracking_wpa) networks can be cracked. This is illegal.

[Firesheep](https://en.wikipedia.org/wiki/Firesheep) intercepts cookies to steal login data over wireless networks. This is illegal.

[Cross Site Scripting](https://en.wikipedia.org/wiki/Cross-site_scripting) (XSS) can be used to inject content into a remote page using a malformed URL.

[People Staring at Computers](http://vimeo.com/groups/openframeworks/videos/25958231) was a photographic study of computer-mediated interaction that turned into a collaboration with Apple and the Secret Service.

[9/11 Pager data](http://911.wikileaks.org/) was a huge release of all the pager messages throughout the day on 9/11.

### Theory

[Does Hacktivism Matter?](http://events.ccc.de/congress/2011/Fahrplan/events/4749.en.html)

[What is in a name?](http://events.ccc.de/congress/2011/Fahrplan/events/4713.en.html) A historical overview, showing "a name never was ones own but always an intersection of administrative, media-technical and personal interventions".

[Critical Engineering Manifesto](http://criticalengineering.org/) is a short document describing how artists might approach technology critically. It comes from the same people who brought you [Newstweek](http://newstweek.com/overview).

Some of the best artistic appropriation comes from the field of bioart, for which [Critical Art Ensemble](http://www.critical-art.net/) is best known. Particularly relevant is the first chapter of [Electronic Civil Disobedience](http://www.critical-art.net/books/ecd/ecd2.pdf).

### Uncategorized

[Video Toaster](https://www.youtube.com/watch?v=C_K8vnx2ZDc) was like the Kinect in that it brought a previously inaccessible technology to a lower price. The interesting thing is the marketing campaign surrounding it: they were genuinely interested in selling it on the idea of bringing down the large networks.

[US Army uses XBox 360 Controller to fly UAVs](http://www.pyrosoft.co.uk/blog/2007/11/04/army-fly-uav-spy-plane-with-xbox-360-controller/)

[Graffiti Markup Language](http://www.graffitimarkuplanguage.com) (GML) uses XML to describe information that would traditionally not have been described with XML.

[Warhol](https://www.youtube.com/watch?v=3oqUd8utr14) was a master of appropriation, all the way down to the Amiga.

["Avoid ghetto" Bing maps feature](http://news.cnet.com/8301-17852_3-57354445-71/the-joy-of-microsofts-avoid-ghetto-gps-patent/). What kind of routes might you suggest?

[BusTime](http://bustime.mta.info/) from the MTA tells us where a bunch of buses are in NYC.

[Siri](https://github.com/applidium/Cracking-Siri#readme) has been reverse engineered, which means you can use Siri on any device. You can also ask questions and get responses in an automated way.

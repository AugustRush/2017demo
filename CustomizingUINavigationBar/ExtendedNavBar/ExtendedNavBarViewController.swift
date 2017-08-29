/*
 Copyright (C) 2016 Apple Inc. All Rights Reserved.
 See LICENSE.txt for this sample’s licensing information
 
 Abstract:
 Demonstrates vertically extending the navigation bar.
 */


import UIKit

class ExtendedNavBarViewController: UIViewController, UITableViewDataSource {
    
    @IBOutlet var tableView: UITableView!
    /// An array of city names, populated from Cities.json.
    var cities = [String]()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        // For the extended navigation bar effect to work, a few changes
        // must be made to the actual navigation bar.  Some of these changes could
        // be applied in the storyboard but are made in code for clarity.
        
        // Translucency of the navigation bar is disabled so that it matches with
        // the non-translucent background of the extension view.
        navigationController!.navigationBar.isTranslucent = false
        
        // The navigation bar's shadowImage is set to a transparent image.  In
        // addition to providing a custom background image, this removes
        // the grey hairline at the bottom of the navigation bar.  The
        // ExtendedNavBarView will draw its own hairline.
        navigationController!.navigationBar.shadowImage = #imageLiteral(resourceName: "TransparentPixel")
        // "Pixel" is a solid white 1x1 image.
        navigationController!.navigationBar.setBackgroundImage(#imageLiteral(resourceName: "Pixel"), for: .default)
        
        // Load some data to populate the table view with
        let citiesJSONURL = #fileLiteral(resourceName: "Cities.json")
        do {
            let citiesJSONData = try Data(contentsOf: citiesJSONURL)
            let jsonObject = try JSONSerialization.jsonObject(with: citiesJSONData, options: JSONSerialization.ReadingOptions(rawValue: UInt(0)))
            if let jsonCities = jsonObject as? [String] {
                cities = jsonCities
            }
        }
        catch {
            return
        }
    }
    
    // MARK: - Table View Data Source
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return cities.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "Cell", for: indexPath)
        cell.textLabel!.text = cities[indexPath.row]
        
        return cell
    }
}
